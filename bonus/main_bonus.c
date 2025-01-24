/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:49:21 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/24 13:14:35 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bonus.h"

int	main(int arg_num, char **args, char **envp)
{
	t_pipex	*pipex;
	t_data	*data;
	size_t	last_child_index;
	size_t	pipe_amount;
	size_t	opt_amount;

	if (arg_num < 5)
		exit(EXIT_FAILURE);
	opt_amount = arg_num - 3;
	pipe_amount = opt_amount - 1;
	last_child_index = arg_num - 5;
	pipex = init_pipex(opt_amount, args, envp);
	data = init_data(pipex, arg_num);
	init_pipes(pipex, pipe_amount);
	process(pipex, envp, last_child_index);
	if (data)
		free(data);
	shut_program_default(pipex, NULL);
}
