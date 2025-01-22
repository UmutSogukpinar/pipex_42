/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:05:35 by umut              #+#    #+#             */
/*   Updated: 2025/01/22 21:11:30 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "unistd.h"
#include "fcntl.h"

void	child(t_pipex *pipex, char *infile, char **envp)
{
	int fd_c;

	fd_c = open(infile, O_RDONLY, 0777);
	if (fd_c < 0)
		shut_program_error(pipex, NULL);
	if (dup2(fd_c, STDIN_FILENO) < 0)
		shut_program_default(pipex, NULL);
	if (dup2((((pipex->opt_list)[0])->fd)[1], STDOUT_FILENO) < 0)
		shut_program_error(pipex, NULL);
	close((((pipex->opt_list)[0])->fd)[0]);
	execute(pipex, (pipex->opt_list)[0], envp);
}

void	parent(t_pipex *pipex, char *outfile, char **envp)
{
	int	fd_p;

	fd_p = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd_p < 0)
		shut_program_error(pipex, NULL);
	if (dup2((((pipex->opt_list)[0])->fd)[1], STDIN_FILENO) < 0)
		shut_program_error(pipex, NULL);
	if (dup2(fd_p, STDOUT_FILENO) < 0)
		shut_program_error(pipex, NULL);
	close((((pipex->opt_list)[0])->fd)[1]);
	execute(pipex, (pipex->opt_list)[1], envp);
}
