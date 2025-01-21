/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:05:35 by umut              #+#    #+#             */
/*   Updated: 2025/01/21 22:58:40 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "unistd.h"
#include "fcntl.h"

void child(t_pipex *pipex, char *infile, char **envp)
{
	int fd_c;

	if (pipe(((pipex->opt_list)[0])->fd) < 0)
		shut_program_error(pipex, NULL);
	fd_c = open(infile, O_RDONLY);
	if (fd_c < 0)
		shut_program_error(pipex, NULL);
	dup2(fd_c, STDIN_FILENO);
	dup2((((pipex->opt_list)[0])->fd)[1], STDOUT_FILENO);
	close((((pipex->opt_list)[0])->fd)[0]);
	execute(pipex, (pipex->opt_list)[0], envp);
}
