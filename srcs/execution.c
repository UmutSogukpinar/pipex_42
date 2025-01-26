/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:52:27 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/26 23:42:27 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include "unistd.h"

static char	*concat_path(t_pipex *pipex, t_operation *opt, int i, char *cmd);

void	execute(t_pipex *pipex, t_operation *opt, char **envp)
{
	char	*path;
	char	**argv;

	path = find_path(pipex, opt);
	if (!path)
		shut_program_error(pipex, CMD_NOT_FOUND);
	argv = opt->cmd_args;
	if (execve(path, argv, envp) == -1)
	{
		close(1);
		close(0);
		shut_program_error(pipex, CMD_NOT_FOUND);
	}
}

char	*find_path(t_pipex *pipex, t_operation *opt)
{
	char	*command;
	char	*temp;
	size_t	i;

	command = (opt->cmd_args)[0];
	i = -1;
	while ((opt->paths)[++i])
	{
		temp = concat_path(pipex, opt, i, command);
		if (access(temp, F_OK | X_OK) == 0)
			return (temp);
		else
			free(temp);
	}
	return (NULL);
}

static char	*concat_path(t_pipex *pipex, t_operation *opt, int i, char *cmd)
{
	size_t	total_size;
	char	*temp;

	total_size = ft_strlen((opt->paths)[i]) + ft_strlen(cmd) + 1;
	temp = malloc(sizeof(char) * total_size);
	if (!temp)
		shut_program_error(pipex, NULL);
	ft_strlcpy(temp, (opt->paths)[i], total_size);
	ft_strlcat(temp, cmd, total_size);
	return (temp);
}
