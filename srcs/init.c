/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:00:42 by umut              #+#    #+#             */
/*   Updated: 2025/01/15 18:10:14 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

static void	***init_cmd_args(t_pipex *pipex, char **args);

t_pipex	*init_pipex(char **args)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex *));
	if (!pipex)
		exit(EXIT_FAILURE);
	init_cmd_args(pipex, args);
	
}

static void	***init_cmd_args(t_pipex *pipex, char **args)
{
	pipex -> cmd_args = malloc(sizeof(char **) * 3);
	if (!(pipex -> cmd_args))
		shut_program_error(pipex);
	(pipex -> cmd_args)[0] = ft_split(args[2], ' ');
	(pipex -> cmd_args)[1] = ft_split(args[3], ' ');
	(pipex -> cmd_args)[2] = NULL;
}
