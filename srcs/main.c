/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:31:51 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/28 16:21:12 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "process.h"
#include "sys/types.h"
#include "unistd.h"

int	main(int arg_num, char **args, char **envp)
{
	t_pipex	*pipex;
	pid_t	pid;

	if (arg_num != 5)
		exit(EXIT_FAILURE);
	pipex = init_pipex(arg_num - 3, args, envp);
	pipex->data = NULL;
	if (pipe(((pipex->opt_list)[0])->fd) < 0)
		shut_program_error(pipex, PIPE_ERR);
	pid = fork();
	if (pid < 0)
		shut_program_error(pipex, PID_ERR);
	else if (pid == 0)
		child(pipex, envp);
	parent(pipex, envp);
	shut_program_default(pipex, NULL);
	return (0);
}
