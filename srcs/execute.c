#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"
#include "feedback.h"
#include "libft.h"

static void	child_process(t_pipex *px, int i, int prev_fd, int pipefd[2]);
static void	parent_process(int i, int count, int *prev_fd, int pipefd[2]);
static void execute_heredoc(t_pipex *pipex);
static void wait_all(t_pipex *pipex, int count, pid_t last_pid);

void execute(t_pipex *pipex)
{
	int	i;
	int	prev_fd;
	int	pipefd[2];
	pid_t	pid;

	prev_fd = -1;
	i = -1;
	while (++i < pipex->cmd_count)
	{
		if (i < pipex->cmd_count - 1 && pipe(pipefd) == -1)
			exit_error(pipex);
		pid = fork();
		if (pid == -1)
			exit_error(pipex);
		if (pid == 0)
			child_process(pipex, i, prev_fd, pipefd);
		parent_process(i, pipex->cmd_count, &prev_fd, pipefd);
		if (i == 0)
		{
			close(pipex->heredoc_fd[READ_END]);
			close(pipex->heredoc_fd[WRITE_END]);
		}
	}
	wait_all(pipex, pipex->cmd_count, pid);
}

static void	child_process(t_pipex *pipex, int i, int prev_fd, int pipefd[2])
{
	if (i == 0 && pipex->here_doc)
		execute_heredoc(pipex);
	else if (i == 0)
		dup2(pipex->fds.in_fd, STDIN_FILENO);
	else
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i == pipex->cmd_count - 1)
		dup2(pipex->fds.out_fd, STDOUT_FILENO);
	else
		dup2(pipefd[WRITE_END], STDOUT_FILENO);
	close(pipefd[READ_END]);
	close(pipefd[WRITE_END]);
	close(pipex->fds.in_fd); 
	close(pipex->fds.out_fd);
	execute_child(pipex, i);
	exit_error("execve failed");
}

static void	parent_process(int i, int count, int *prev_fd, int pipefd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i < count - 1)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

static void wait_all(t_pipex *pipex, int count, pid_t last_pid)
{
    int     status;
    pid_t   pid;
    int     i;

    i = 0;
    while (i < count)
    {
        pid = wait(&status);
        if (pid == -1)
            break;
        if (pid == last_pid)
        {
            if (WIFEXITED(status))
                pipex->exit_no = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                pipex->exit_no = 128 + WTERMSIG(status);
        }
        i++;
    }
}

static void execute_heredoc(t_pipex *pipex)
{
	pid_t	pid;
	char	*input;
	// TODO: Implement GNL
	input = get_next_line(STDIN_FILENO);
	while (input)
	{
		write(pipex->heredoc_fd[WRITE_END], input, ft_strlen(input));
		input = get_next_line(STDIN_FILENO);
	}
	dup2(pipex->heredoc_fd[READ_END], STDIN_FILENO);
	close(pipex->heredoc_fd[READ_END]);
	close(pipex->heredoc_fd[WRITE_END]);
	free_gnl();
}
