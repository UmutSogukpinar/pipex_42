/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:05:19 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/28 14:48:15 by usogukpi         ###   ########.fr       */
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

typedef struct s_data
{
	int			pipe_amount;
	int			lst_child_index;
	int			opt_amount;
	int			arg_num;

}				t_data;

typedef struct s_pipex
{
	t_operation	**opt_list;
	t_data		*data;
	size_t		list_size;
	char		*infile;
	char		*outfile;

}				t_pipex;

t_pipex			*init_pipex(size_t size, char **args, char **envp);
t_operation		*init_opt(t_pipex *pipex, char *args, char **envp);
void			shut_program_error(t_pipex *pipex, char *message);
void			shut_program_default(t_pipex *pipex, char *message);
void			free_pipex(t_pipex *pipex);

char			*find_path(t_pipex *pipex, t_operation *opt);
void			execute(t_pipex *pipex, t_operation *opt, char **envp);

# define CMD_NOT_FOUND "Command not found"
# define EXECVE_ERR "Execve stops working"
# define DUP2_ERR "Dup2 function fails"
# define INFILE_ERR "Infile could not be opened"
# define OUTFILE_ERR "Outfile could not be opened"
# define PIPE_ERR "Pipe stops working"
# define PID_ERR "Fork stops working"

#endif