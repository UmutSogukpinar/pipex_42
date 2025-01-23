/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:41:48 by umut              #+#    #+#             */
/*   Updated: 2025/01/24 00:56:26 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "pipex.h"

t_data *init_data(t_pipex *pipex, int arg_num)
{
	size_t	last_child_index;
	size_t	pipe_amount;
	size_t	opt_amount;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		shut_program_error(pipex, NULL);
	opt_amount = arg_num - 3;
	pipe_amount = opt_amount - 1;
	last_child_index = arg_num - 5;
	data -> lst_child_index = last_child_index;
	data -> pipe_amount = pipe_amount;
	data -> opt_amount = opt_amount;
	data -> arg_num = arg_num;
	return (data);
}
