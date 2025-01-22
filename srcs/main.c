/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:31:46 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/22 21:19:29 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/types.h"
#include "unistd.h"
#include "pipex.h"
#include "process.h"

int	main(int arg_num, char **args, char **envp)
{
	t_pipex	*pipex;
	pid_t	pid;

	if (arg_num != 5)
		exit(EXIT_FAILURE);
	pipex = init_pipex(arg_num - 3, args, envp);
	if (pipe(((pipex->opt_list)[0])->fd) < 0)
		shut_program_error(pipex, NULL);
	pid = fork();
	if (pid < 0)
		shut_program_error(pipex, NULL);
	else if (pid == 0)
		child(pipex, args[1], envp);
	parent(pipex, args[4], envp);
    shut_program_default(pipex, NULL);
	return (0);
}
