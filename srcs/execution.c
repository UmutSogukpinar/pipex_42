/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:52:27 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/21 18:42:47 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "pipex.h"
#include "unistd.h"

static char	*concat_path(t_pipex *pipex, t_operation *opt, int i, char *cmd);

void	execute(t_pipex *pipex, t_operation *opt, char **envp)
{
	char	*path;

	path = find_path(pipex, opt);
	if (execve(path, opt->cmd_args, envp) == -1)
	{
        ft_putstr_fd("command not found: ", 2);
        ft_putendl_fd((opt -> cmd_args)[0], 2);
		shut_program_default(pipex, NULL);
	}
}

char	*find_path(t_pipex *pipex, t_operation *opt)
{
	char	*command;
	char	*temp;
	size_t	i;
	size_t	total_size;

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
