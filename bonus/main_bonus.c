/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:49:21 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/28 00:23:50 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "pipex.h"
#include "stdio.h"
#include "sys/types.h"
#include "unistd.h"

static void	normal_path(int arg_num, char **args, char **envp);
static void	here_doc_path(int arg_num, char **args, char **envp);

int	main(int arg_num, char **args, char **envp)
{
	if (arg_num < 5)
		exit(EXIT_FAILURE);
	if (is_strs_equals("here_doc", args[1]))
		here_doc_path(arg_num, args, envp);
	else
		normal_path(arg_num, args, envp);
	return (0);
}

static void	normal_path(int arg_num, char **args, char **envp)
{
	t_pipex	*pipex;
	t_data	*data;
	size_t	pipe_amount;
	size_t	opt_amount;

	opt_amount = arg_num - 3;
	pipe_amount = opt_amount - 1;
	pipex = init_pipex(opt_amount, args, envp);
	data = init_data(pipex, arg_num);
	pipex->data = data;
	init_pipes(pipex, pipe_amount);
	process(pipex, envp, data);
	shut_program_default(pipex, NULL);
}

static void	here_doc_path(int arg_num, char **args, char **envp)
{
	t_pipex	*pipex;
	pid_t	pid;
	pid_t	pid2;

	if (arg_num != 6)
		exit(EXIT_SUCCESS);
	pipex = init_here_doc_pipex(arg_num - 4, args, envp);
	if (pipe(((pipex->opt_list)[0])->fd) < 0
		|| pipe(((pipex->opt_list)[1])->fd) < 0)
		shut_program_error(pipex, NULL);
	pid = fork();
	if (pid < 0)
		shut_program_error(pipex, NULL);
	else if (pid == 0)
		here_doc_one(pipex, args);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			shut_program_error(pipex, NULL);
		else if (pid2 == 0)
			here_doc_two(pipex, envp);
		else
			here_doc_three(pipex, envp);
	}
}
