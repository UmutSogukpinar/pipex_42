/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shut.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:15:38 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/26 23:35:56 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "unistd.h"

static void	free_double_pntr(char **array);
static void	free_operation(t_operation *opt);

void	shut_program_error(t_pipex *pipex, char *message)
{
	unlink(pipex->outfile);
	if (message)
		ft_putendl_fd(message, 2);
	free_pipex(pipex);
	exit(EXIT_FAILURE);
}

void	shut_program_default(t_pipex *pipex, char *message)
{
	if (message)
		ft_putendl_fd(message, 1);
	free_pipex(pipex);
	exit(EXIT_SUCCESS);
}

void	free_pipex(t_pipex *pipex)
{
	size_t	i;

	if (pipex)
	{
		if (pipex->opt_list)
		{
			i = -1;
			while ((pipex->opt_list)[++i])
				free_operation((pipex->opt_list)[i]);
			free(pipex->opt_list);
		}
		if (pipex->infile)
			free(pipex->infile);
		if (pipex->outfile)
			free(pipex->outfile);
		free(pipex);
	}
}

static void	free_operation(t_operation *opt)
{
	if (opt)
	{
		free_double_pntr(opt->paths);
		free_double_pntr(opt->cmd_args);
	}
	free(opt);
}

static void	free_double_pntr(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
