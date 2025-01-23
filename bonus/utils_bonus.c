/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:19:40 by umut              #+#    #+#             */
/*   Updated: 2025/01/23 23:39:18 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "pipex.h"
#include "unistd.h"
#include "stdio.h"

int	open_file(t_pipex *pipex, char *name, int is_child)
{
	int	fd;


	printf("is child: %d and name is: %s\n", is_child, name);
	if (is_child)
		fd = open(name, O_RDONLY);
	else
		fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
		shut_program_error(pipex, NULL);
	return (fd);
}

void	init_pipes(t_pipex *pipex, size_t amount)
{
	size_t i;

	i = -1;
	while (++i < amount)
	{
		if (pipe(((pipex->opt_list)[i])->fd) < 0)
			shut_program_error(pipex, NULL);
	}
}
