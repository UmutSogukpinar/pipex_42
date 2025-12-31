#include <stdio.h>
#include <stdlib.h>
#include "pipex.h"
#include "feedback.h"

/**
 * Frees a NULL-terminated array of strings.
 *
 * Safely handles NULL input.
 *
 * @param v (char **): String vector to free
 */
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

/**
 * Frees all resources associated with the pipex structure.
 *
 * - Frees PATH array
 * 
 * - Frees command array (shallow free)
 * 
 * - Closes all file descriptors
 * 
 * - Frees the pipex structure itself
 *
 * Safely handles NULL input.
 *
 * @param pipex (t_pipex *): Pipex structure to destroy
 */
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

/**
 * Frees all allocated pipex resources, prints a system error,
 * and terminates the program with EXIT_FAILURE (1).
 *
 * @param pipex (t_pipex *): Pipex structure to clean before exiting
 */
void	exit_error(t_pipex *pipex)
{
	free_pipex(pipex);
	perror(ERROR);
	exit(EXIT_FAILURE);
}
