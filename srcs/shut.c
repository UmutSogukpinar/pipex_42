/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shut.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:48:16 by umut              #+#    #+#             */
/*   Updated: 2025/01/15 17:59:01 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdlib.h"

static void	free_double_pntr(char **array);

void	shut_program_error(t_pipex *pipex)
{
	free_program(pipex);
	exit(EXIT_FAILURE);
}

void	free_program(t_pipex *pipex)
{
	size_t	i;

	if (pipex)
	{
		if (pipex -> cmd_args)
		{
			i = -1;
			while ((pipex -> cmd_args)[++i])
				free_double_pntr((pipex -> cmd_args)[++i]);
			free(pipex -> cmd_args);
		}
		free(pipex);
	}
}

static void	free_double_pntr(char **array)
{
	size_t	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
