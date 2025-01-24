/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:31:46 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/24 13:06:13 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "pipex.h"
#include "unistd.h"

void	child(t_pipex *pipex, char **envp)
{
	int	infile_fd;

	infile_fd = open(pipex->infile, O_RDONLY);
	if (infile_fd < 0)
		shut_program_error(pipex, NULL);
	if (dup2(infile_fd, STDIN_FILENO) < 0)
		shut_program_default(pipex, NULL);
	if (dup2((((pipex->opt_list)[0])->fd)[1], STDOUT_FILENO) < 0)
		shut_program_error(pipex, NULL);
	close((((pipex->opt_list)[0])->fd)[0]);
	close((((pipex->opt_list)[0])->fd)[1]);
	close(infile_fd);
	execute(pipex, (pipex->opt_list)[0], envp);
}

void	parent(t_pipex *pipex, char **envp)
{
	int	outfile_fd;

	outfile_fd = open(pipex->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (outfile_fd < 0)
		shut_program_error(pipex, NULL);
	if (dup2((((pipex->opt_list)[0])->fd)[0], STDIN_FILENO) < 0)
		shut_program_error(pipex, NULL);
	if (dup2(outfile_fd, STDOUT_FILENO) < 0)
		shut_program_error(pipex, NULL);
	close((((pipex->opt_list)[0])->fd)[1]);
	close((((pipex->opt_list)[0])->fd)[0]);
	close(outfile_fd);
	execute(pipex, (pipex->opt_list)[1], envp);
}
