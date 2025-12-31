#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"
#include "feedback.h"

// TODO: could turn into static !!!
void	free_strv(char **v)
{
	size_t	i;

	if (!v)
		return ;
	i = 0;
	while (v[i])
	{
		free(v[i]);
		i++;
	}
	free(v);
}

void	free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	free_strv(pipex->paths);
	free(pipex->cmds);
	if (pipex->fds.in_fd > 0)
		close(pipex->fds.in_fd);
	if (pipex->fds.out_fd > 0)
		close(pipex->fds.out_fd);
	if (pipex->heredoc_fd[0] > 0)
		close(pipex->heredoc_fd[0]);
	if (pipex->heredoc_fd[1] > 0)
		close(pipex->heredoc_fd[1]);
	free(pipex);
}

void	exit_error(t_pipex *pipex)
{
	free_pipex(pipex);
	perror(ERROR);
	exit(EXIT_FAILURE);
}
