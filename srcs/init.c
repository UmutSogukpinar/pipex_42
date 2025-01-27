/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:06:00 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/27 14:23:06 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static void			init_cmd_args(t_pipex *pipex, t_operation *opt, char *args);
static void			init_paths(t_pipex *pipex, t_operation *opt, char **envp);
static char			*add_slash(t_pipex *pipex, char *old);

t_pipex	*init_pipex(size_t size, char **args, char **envp)
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
	while (i < size)
	{
		(pipex->opt_list)[i] = init_opt(pipex, args[i + 2], envp);
		i++;
	}
	(pipex->opt_list)[i] = NULL;
	pipex->infile = ft_strdup(args[1]);
	pipex->outfile = ft_strdup(args[size + 2]);
	if (!(pipex->infile) || !(pipex->outfile))
		shut_program_error(pipex, NULL);
	return (pipex);
}

t_operation	*init_opt(t_pipex *pipex, char *args, char **envp)
{
	t_operation	*opt;

	opt = malloc(sizeof(t_operation));
	if (!opt)
		shut_program_error(pipex, NULL);
	init_cmd_args(pipex, opt, args);
	init_paths(pipex, opt, envp);
	return (opt);
}

static void	init_cmd_args(t_pipex *pipex, t_operation *opt, char *args)
{
	char	**temp;

	temp = ft_split(args, ' ');
	if (!temp)
		shut_program_error(pipex, NULL);
	opt->cmd_args = temp;
}

static void	init_paths(t_pipex *pipex, t_operation *opt, char **envp)
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			opt->paths = ft_split(envp[i] + 5, ':');
			if (!(opt->paths))
				shut_program_error(pipex, NULL);
			j = -1;
			while ((opt->paths)[++j])
				(opt->paths)[j] = add_slash(pipex, (opt->paths)[j]);
			return ;
		}
	}
	shut_program_error(pipex, NULL);
}

static char	*add_slash(t_pipex *pipex, char *old)
{
	size_t	total_size;
	char	*new;

	total_size = ft_strlen(old) + 1 + 1;
	new = malloc(total_size);
	if (!new)
		shut_program_error(pipex, NULL);
	ft_strlcpy(new, old, total_size);
	ft_strlcat(new, "/", total_size);
	free(old);
	return (new);
}
