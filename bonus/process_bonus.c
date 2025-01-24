/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:10:24 by umut              #+#    #+#             */
/*   Updated: 2025/01/24 13:45:47 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "sys/types.h"
#include "unistd.h"
#include "bonus.h"

static void	child_rec(t_pipex *pipex, char **envp, size_t index, t_data *data);
static void	parent(t_pipex *pipex, char **envp, size_t opt);
static void	first_child(t_pipex *pipex, char **envp, t_data *data);
static void	execution(t_pipex *pipex, t_data *data, char **envp, size_t index);

void	process(t_pipex *pipex, char **envp, t_data *data)
{
	pid_t	pid;
	int		last_child_index;

	last_child_index = data -> lst_child_index;
	pid = fork();
	if (pid < 0)
	{
		free_data(data);
		shut_program_error(pipex, NULL);
	}	
	else if (pid == 0)
		child_rec(pipex, envp, last_child_index, data);
	parent(pipex, envp, last_child_index);
}

static void	child_rec(t_pipex *pipex, char **envp, size_t index, t_data *data)
{
	pid_t	pid;

	if (index == 0)
		first_child(pipex, envp, data);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			free_data(data);
			shut_program_error(pipex, NULL);
		}
		else if (pid == 0)
			child_rec(pipex, envp, index - 1, data);
		else
			execution(pipex, data, envp, index);
	}
}

static void	parent(t_pipex *pipex, char **envp, size_t index)
{
	int	outfile_fd;

	outfile_fd = open_file(pipex, pipex->outfile, 0);
	if (dup2((((pipex->opt_list)[index])->fd)[0], STDIN_FILENO) < 0)
		shut_program_error(pipex, NULL);
	if (dup2(outfile_fd, STDOUT_FILENO) < 0)
		shut_program_error(pipex, NULL);
	close_unused_pipes_one(pipex, index + 1);
	execute(pipex, (pipex->opt_list)[index + 1], envp);
}

static void	first_child(t_pipex *pipex, char **envp, t_data *data)
{
	int	infile_fd;

	infile_fd = open_file(pipex, pipex->infile, 1);
	if (dup2(infile_fd, STDIN_FILENO) < 0)
		shut_program_error(pipex, NULL);
	if (dup2((((pipex->opt_list)[0])->fd)[1], STDOUT_FILENO) < 0)
		shut_program_error(pipex, NULL);
	close_unused_pipes_one(pipex, data->pipe_amount);
	execute(pipex, (pipex->opt_list)[0], envp);
}

static void	execution(t_pipex *pipex, t_data *data, char **envp, size_t index)
{
	if (dup2(((pipex->opt_list)[index - 1])->fd[0], STDIN_FILENO) < 0)
    {
		free_data(data);
		shut_program_error(pipex, NULL);
	}
    if (dup2(((pipex->opt_list)[index])->fd[1], STDOUT_FILENO) < 0)
	{
		free_data(data);
		shut_program_error(pipex, NULL);
	}
 	close_unused_pipes_one(pipex, data->pipe_amount);
	execute(pipex, (pipex->opt_list)[index], envp);
}
