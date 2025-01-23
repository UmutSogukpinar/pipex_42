/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:28:01 by umut              #+#    #+#             */
/*   Updated: 2025/01/23 22:36:48 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "pipex.h"

void	process(t_pipex *pipex, char **args, char **envp, size_t last);
int		open_file(t_pipex *pipex, char *name, int is_child);
void	init_pipes(t_pipex *pipex, size_t amount);

#endif