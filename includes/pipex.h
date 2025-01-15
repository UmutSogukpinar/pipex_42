/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:36:56 by umut              #+#    #+#             */
/*   Updated: 2025/01/15 19:35:22 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipex
{
	int		fd[2];
	char	***cmd_args;
	char	**paths;
	
}	t_pipex;

t_pipex	*init_pipex(char **args, char **envp);
void	shut_program_error(t_pipex *pipex, const char *message);

#endif