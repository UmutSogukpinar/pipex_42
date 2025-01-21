/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:52:27 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/21 23:27:00 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "pipex.h"
#include "unistd.h"

static char	*concat_path(t_pipex *pipex, t_operation *opt, int i, char *cmd);
static char	**copy_str_array(char **original);
static char	**copy_str_array_helper(char **arr, int i);

void	execute(t_pipex *pipex, t_operation *opt, char **envp)
{
	char	*path;
	char	**argv;

	path = find_path(pipex, opt);
	argv = copy_str_array(opt->cmd_args);
	free_pipex(pipex);
	if (execve(path, argv, envp) == -1)
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

static char	**copy_str_array(char **original)
{
	int		i;
	int		count;
	char	**copy;

	count = 0;
	while (original[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
		{
			copy_str_arr_helper(copy, i);
			return (NULL);
		}
	}
	copy[count] = NULL;
	return (copy);
}

static void	copy_str_arr_helper(char **arr, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(arr[j]);
	free(arr);
}
