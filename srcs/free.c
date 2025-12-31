#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"
#include "feedback.h"

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
	close_fd(&(pipex->fds.in_fd));
	close_fd(&(pipex->fds.out_fd));
	close_fd(&(pipex->heredoc_fd[READ_END]));
	close_fd(&(pipex->heredoc_fd[WRITE_END]));
	free(pipex);
}

void	exit_error(t_pipex *pipex)
{
	free_pipex(pipex);
	perror(ERROR);
	exit(EXIT_FAILURE);
}
