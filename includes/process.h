/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:07:50 by umut              #+#    #+#             */
/*   Updated: 2025/01/22 21:19:15 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "pipex.h"

void	child(t_pipex *pipex, char *infile, char **envp);
void	parent(t_pipex *pipex, char *outfile, char **envp);

#endif