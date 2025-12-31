#include <fcntl.h>
#include <unistd.h>

#include "pipex.h"

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
