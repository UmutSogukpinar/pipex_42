/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:36:56 by umut              #+#    #+#             */
/*   Updated: 2025/01/15 18:03:16 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipex
{
	int		fd[2];
	char	***cmd_args;
	
}	t_pipex;

void	shut_program_error(t_pipex *pipex);
void	free_program(t_pipex *pipex);

#endif