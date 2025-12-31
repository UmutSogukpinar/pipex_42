#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"
#include "feedback.h"
#include "libft.h"
#include "get_next_line.h"

static void prepare_heredoc(t_pipex *pipex);
static void child_process(t_pipex *pipex, int i, int prev_fd, int pipefd[2]);
static void parent_process(int i, int count, int *prev_fd, int pipefd[2]);
static void wait_all(t_pipex *pipex, int count, pid_t last_pid);

void execute(t_pipex *pipex)
{
    int     i;
    int     prev_fd;
    int     pipefd[2];
    pid_t   pid;

    prev_fd = -1;
    i = 0;
    if (pipex->here_doc)
        prepare_heredoc(pipex);
    while (i < pipex->cmd_count)
    {
        if (i < pipex->cmd_count - 1 && pipe(pipefd) == -1)
            exit_error(pipex);
        pid = fork();
        if (pid == -1)
            exit_error(pipex);
        if (pid == 0)
            child_process(pipex, i, prev_fd, pipefd);
        parent_process(i, pipex->cmd_count, &prev_fd, pipefd);
        i++;
    }
    wait_all(pipex, pipex->cmd_count, pid);
}

static void child_process(t_pipex *pipex, int i, int prev_fd, int pipefd[2])
{
    if (i == 0)
    {
		init_infile(pipex);
        if (pipex->here_doc)
            dup2(pipex->heredoc_fd[READ_END], STDIN_FILENO);
        else
            dup2(pipex->fds.in_fd, STDIN_FILENO);
    }
    else
    {
        dup2(prev_fd, STDIN_FILENO);
        close_fd(&prev_fd);
    }
    if (i == pipex->cmd_count - 1)
	{
		init_outfile(pipex);
        dup2(pipex->fds.out_fd, STDOUT_FILENO);
	}
    else
        dup2(pipefd[WRITE_END], STDOUT_FILENO);
    if (i < pipex->cmd_count - 1)
    {
        close_fd(&(pipefd[READ_END]));
        close_fd(&(pipefd[WRITE_END]));
    }
    close_fd(&(pipex->fds.out_fd));
    if (pipex->here_doc)
        close_fd(&(pipex->heredoc_fd[READ_END]));
    execute_child(pipex, i);
}

static void parent_process(int i, int count, int *prev_fd, int pipefd[2])
{
    if (*prev_fd != -1)
        close_fd(prev_fd);
    if (i < count - 1)
    {
        close_fd(&(pipefd[WRITE_END]));
        *prev_fd = pipefd[READ_END];
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

static void prepare_heredoc(t_pipex *pipex)
{
    char *line;

	line = get_next_line(STDIN_FILENO);
    while (line)
    {
        if (!ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter))
            && line[ft_strlen(pipex->limiter)] == '\n')
        {
            free(line);
            break;
        }
        write(pipex->heredoc_fd[WRITE_END], line, ft_strlen(line));
        free(line);
		line = get_next_line(STDIN_FILENO);
    }
	free_gnl();
    close_fd(&(pipex->heredoc_fd[WRITE_END]));
}
