/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:49:21 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/25 15:44:32 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "pipex.h"
#include "unistd.h"
#include "sys/types.h"

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
	init_pipes(pipex, pipe_amount);
	process(pipex, envp, data);
	if (data)
		free(data);
	shut_program_default(pipex, NULL);
}

static void	here_doc_path(int arg_num, char **args, char **envp)
{
	t_pipex	*pipex;
	int		fd[2];
	pid_t	pid;
	
	if (arg_num != 6)
		exit(EXIT_SUCCESS);
	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		here_doc_input(args, fd);
	else
		here_doc_output(args, fd, envp);
}
