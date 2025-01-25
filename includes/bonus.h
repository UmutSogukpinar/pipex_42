/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:04:34 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/25 15:42:36 by usogukpi         ###   ########.fr       */
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

}		t_data;

void	process(t_pipex *pipex, char **envp, t_data *data);
int		open_file(t_pipex *pipex, char *name, int is_child);
void	init_pipes(t_pipex *pipex, size_t amount);
t_data	*init_data(t_pipex *pipex, int arg_num);
void	close_unused_pipes_one(t_pipex *pipex, size_t amount);
void	free_data(t_data *data);
int		is_strs_equals(char *s1, char *s2);
void	here_doc_input(char **args, int fd[]);

#endif