/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:05:19 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/25 14:49:25 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "stdlib.h"

typedef struct s_operation
{
	int			fd[2];
	char		**cmd_args;
	char		**paths;

}				t_operation;

typedef struct s_pipex
{
	t_operation	**opt_list;
	size_t		list_size;
	char		*infile;
	char		*outfile;

}				t_pipex;

t_pipex			*init_pipex(size_t size, char **args, char **envp);
void			shut_program_error(t_pipex *pipex, const char *message);
void			shut_program_default(t_pipex *pipex, const char *message);
void			free_pipex(t_pipex *pipex);

char			*find_path(t_pipex *pipex, t_operation *opt);
void			execute(t_pipex *pipex, t_operation *opt, char **envp);

#endif