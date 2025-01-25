/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:03:41 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/25 15:49:56 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "fcntl.h"
#include "libft.h"
#include "pipex.h"
#include "unistd.h"

int	open_file(t_pipex *pipex, char *name, int is_child)
{
	int	fd;

	if (is_child)
		fd = open(name, O_RDONLY);
	else
		fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
		shut_program_error(pipex, NULL);
	return (fd);
}

void	close_unused_pipes_one(t_pipex *pipex, size_t amount)
{
	size_t	i;

	i = 0;
	while (i < amount)
	{
		if ((pipex->opt_list)[i] != NULL)
		{
			close(((pipex->opt_list)[i])->fd[0]);
			close(((pipex->opt_list)[i])->fd[1]);
		}
		i++;
	}
}

void	free_data(t_data *data)
{
	if (data)
		free(data);
}

int	is_strs_equals(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	return (ft_strlen(s1) == ft_strlen(s2) && ft_strncmp(s1, s2,
			ft_strlen(s2)));
}
