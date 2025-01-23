/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:49:21 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/23 15:22:45 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdio.h"

void	display_pipex(t_pipex *pipex)
{
	t_operation	*opt;

	if (!pipex)
	{
		printf("Pipex is NULL.\n");
		return ;
	}
	printf("Pipex Object:\n");
	printf("List Size: %zu\n", pipex->list_size);
	for (size_t i = 0; i < pipex->list_size; i++)
	{
		opt = pipex->opt_list[i];
		if (!opt)
		{
			printf("Operation %zu: NULL\n", i);
			continue ;
		}
		printf("Operation %zu:\n", i);
		printf("  fd[0]: %d\n", opt->fd[0]);
		printf("  fd[1]: %d\n", opt->fd[1]);
		printf("  cmd_args:\n");
		if (opt->cmd_args)
		{
			for (size_t j = 0; opt->cmd_args[j]; j++)
				printf("    [%zu]: %s\n", j, opt->cmd_args[j]);
		}
		else
		{
			printf("    cmd_args is NULL.\n");
		}
		printf("  paths:\n");
		if (opt->paths)
		{
			for (size_t j = 0; opt->paths[j]; j++)
				printf("    [%zu]: %s\n", j, opt->paths[j]);
		}
		else
		{
			printf("    paths is NULL.\n");
		}
	}
}

int	main(int arg_num, char **args, char **envp)
{
	t_pipex	*pipex;

	if (arg_num < 5)
		exit(EXIT_FAILURE);
	pipex = init_pipex(arg_num - 3, args, envp);
	display_pipex(pipex);
	shut_program_default(pipex, NULL);
}
