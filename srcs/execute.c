#include <sys/types.h>
#include <unistd.h>
#include "pipex.h"

static void	child_process(t_pipex *px, int i, int prev_fd, int pipefd[2]);
static void	parent_process(int i, int count, int *prev_fd, int pipefd[2]);
static void	wait_all(int count);

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
			exit_error("pipe failed");

		pid = fork();
		if (pid == -1)
			exit_error("fork failed");

		if (pid == 0)
			child_process(pipex, i, prev_fd, pipefd);
		parent_process(i, pipex->cmd_count, &prev_fd, pipefd);
	}
	wait_all(pipex->cmd_count);
}

static void	child_process(t_pipex *pipex, int i, int prev_fd, int pipefd[2])
{
	if (i == 0)
		dup2(pipex->fds.in_fd, STDIN_FILENO);
	else
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i == pipex->cmd_count - 1)
		dup2(pipex->fds.out_fd, STDOUT_FILENO);
	else
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
    // TODO: Implement executon function
	execve(pipex->cmd_paths[i], pipex->cmds[i], pipex->envp);
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

static void	wait_all(int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
        // TODO: Implement macros
		wait(NULL);
		i++;
	}
}

