#include <fcntl.h>
#include "pipex.h"

/**
 * Opens the input file for reading in normal (non-heredoc) mode.
 *
 * If heredoc mode is enabled, this function does nothing.
 * On failure, closes already opened output file and exits
 * the program with an error.
 *
 * @param pipex Pipex structure containing infile information
 */
void    init_infile(t_pipex *pipex)
{
    if (!pipex->here_doc)
    {
        pipex->fds.in_fd = open(pipex->infile, O_RDONLY);
		if (pipex->fds.in_fd < 0)
		{
			close_fd(&(pipex->fds.out_fd));
			exit_error(pipex);
		}
    }
}

/**
 * Opens the output file according to execution mode.
 *
 * - Heredoc mode:
 *   Opens the file in append mode.
 *
 * - Normal mode:
 *   Creates or truncates the file before writing.
 *
 * On failure, exits the program with an error.
 *
 * @param pipex (t_pipex *): Pipex structure containing outfile information
 */
void    init_outfile(t_pipex *pipex)
{
    if (pipex->here_doc)
	{
		pipex->fds.out_fd = open(pipex->outfile, O_CREAT | O_APPEND | O_WRONLY);
		if (pipex->fds.out_fd < 0)
			exit_error(pipex);
    }
    else
	{
		pipex->fds.out_fd = open(pipex->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		if (pipex->fds.out_fd < 0)
			exit_error(pipex);
    }
}
