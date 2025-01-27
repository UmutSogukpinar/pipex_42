/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:55:17 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/27 19:47:04 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "fcntl.h"
#include "get_next_line.h"
#include "libft.h"
#include "pipex.h"
#include "stdio.h"
#include "unistd.h"

static char	*update_w_newline(char *str);

void	here_doc_one(t_pipex *pipex, char **args)
{
	char	*input;
	char	*limiter;

	limiter = update_w_newline(args[2]);
	if (!limiter)
		shut_program_error(pipex, NULL);
	close(pipex->opt_list[0]->fd[0]);
	close(pipex->opt_list[1]->fd[0]);
	close(pipex->opt_list[1]->fd[1]);
	input = get_next_line(0);
	while (input)
	{
		if (is_strs_equals(input, limiter))
		{
			free(input);
			break ;
		}
		write(pipex->opt_list[0]->fd[1], input, ft_strlen(input));
		free(input);
		input = get_next_line(0);
	}
	free(limiter);
	finish_gnl(pipex);
	close(pipex->opt_list[0]->fd[1]);
	shut_program_default(pipex, NULL);
}

void	here_doc_two(t_pipex *pipex, char **envp)
{
	if (dup2((pipex->opt_list[0])->fd[0], STDIN_FILENO) < 0)
		shut_program_error(pipex, NULL);
	if (dup2((pipex->opt_list[1])->fd[1], STDOUT_FILENO) < 0)
		shut_program_error(pipex, NULL);
	close_unused_pipes_one(pipex, 2);
	execute(pipex, (pipex->opt_list)[0], envp);
}

void	here_doc_three(t_pipex *pipex, char **envp)
{
	int	outfile_fd;

	outfile_fd = open(pipex->outfile, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (dup2((pipex->opt_list[1])->fd[0], STDIN_FILENO) < 0)
		shut_program_error(pipex, NULL);
	if (dup2(outfile_fd, STDOUT_FILENO) < 0)
		shut_program_error(pipex, NULL);
	close_unused_pipes_one(pipex, 2);
	execute(pipex, (pipex->opt_list)[1], envp);
}

t_pipex	*init_here_doc_pipex(size_t size, char **args, char **envp)
{
	t_pipex	*pipex;
	size_t	i;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		exit(EXIT_FAILURE);
	pipex->list_size = size;
	pipex->opt_list = malloc(sizeof(t_operation *) * (size + 1));
	if (!(pipex->opt_list))
		shut_program_error(pipex, NULL);
	i = 0;
	while (i < (pipex->list_size))
	{
		(pipex->opt_list)[i] = init_opt(pipex, args[i + 3], envp);
		i++;
	}
	(pipex->opt_list)[i] = NULL;
	pipex->infile = NULL;
	pipex->outfile = ft_strdup(args[size + 3]);
	if (!(pipex->outfile))
		shut_program_error(pipex, NULL);
	return (pipex);
}

static char	*update_w_newline(char *str)
{
	int		i;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = '\n';
	new[i] = '\0';
	return (new);
}
