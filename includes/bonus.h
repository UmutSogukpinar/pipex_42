/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:28:01 by umut              #+#    #+#             */
/*   Updated: 2025/01/24 12:57:44 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "pipex.h"

typedef struct s_data
{
	int	pipe_amount;
	int	lst_child_index;
	int	opt_amount;
	int	arg_num;

}	t_data;


void	process(t_pipex *pipex, char **args, char **envp, t_data *data);
int		open_file(t_pipex *pipex, char *name, int is_child);
void	init_pipes(t_pipex *pipex, size_t amount);
t_data *init_data(t_pipex *pipex, int arg_num);
void close_unused_pipes_one(t_pipex *pipex, size_t amount);

#endif