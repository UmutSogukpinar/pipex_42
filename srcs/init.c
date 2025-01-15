/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:00:42 by umut              #+#    #+#             */
/*   Updated: 2025/01/15 19:01:39 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

static void	init_cmd_args(t_pipex *pipex, char **args);
static void	init_paths(t_pipex *pipex, char **envp);

t_pipex	*init_pipex(char **args, char **envp)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		exit(EXIT_FAILURE);
	init_cmd_args(pipex, args);
	init_paths(pipex, envp);
	return (pipex);
}

static void	init_cmd_args(t_pipex *pipex, char **args)
{
	char	***temp;
	temp = malloc(sizeof(char **) * 3);
	if (!temp)
		shut_program_error(pipex, NULL);
	temp[0] = ft_split(args[2], ' ');
	temp[1] = ft_split(args[3], ' ');
	if (!(temp[0]) || !(temp[1]))
	{
		free(temp);
		shut_program_error(pipex, NULL);
	}
	temp[2] = NULL;
	pipex -> cmd_args = temp;
}

static void	init_paths(t_pipex *pipex, char **envp)
{
	size_t	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			pipex -> paths = ft_split(envp[i] + 5, ':');
			if (!(pipex -> paths))
				shut_program_error(pipex, NULL);
			return ;
		}
	}
	shut_program_error(pipex, NULL);
}
