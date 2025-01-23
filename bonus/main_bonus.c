/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:49:21 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/23 23:15:42 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bonus.h"

int	main(int arg_num, char **args, char **envp)
{
	t_pipex	*pipex;
	size_t	last_child_index;
	size_t	pipe_amount;
	size_t	opt_amount;

	if (arg_num < 5)
		exit(EXIT_FAILURE);
	opt_amount = arg_num - 3;
	pipex = init_pipex(opt_amount, args, envp);
	pipe_amount = opt_amount - 1;
	init_pipes(pipex, pipe_amount);
	last_child_index = arg_num - 5;
	process(pipex, args, envp, last_child_index);
	shut_program_default(pipex, NULL);
}
