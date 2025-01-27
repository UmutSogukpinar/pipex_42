/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:04:34 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/27 19:47:22 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "pipex.h"

void	process(t_pipex *pipex, char **envp, t_data *data);
int		open_file(t_pipex *pipex, char *name, int is_child);
void	init_pipes(t_pipex *pipex, size_t amount);
t_data	*init_data(t_pipex *pipex, int arg_num);
void	close_unused_pipes_one(t_pipex *pipex, size_t amount);
void	free_data(void *data);
int		is_strs_equals(char *s1, char *s2);
t_pipex	*init_here_doc_pipex(size_t size, char **args, char **envp);
void	here_doc_one(t_pipex *pipex, char **args);
void	here_doc_two(t_pipex *pipex, char **envp);
void	here_doc_three(t_pipex *pipex, char **envp);
void	finish_gnl(t_pipex *pipex);

#endif