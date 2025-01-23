/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:32:18 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/23 13:32:21 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "pipex.h"

void	child(t_pipex *pipex, char *infile, char **envp);
void	parent(t_pipex *pipex, char *outfile, char **envp);

#endif