/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:19:40 by umut              #+#    #+#             */
/*   Updated: 2025/01/24 12:57:40 by umut             ###   ########.fr       */
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

void close_unused_pipes_one(t_pipex *pipex, size_t amount)
{
    size_t i;

    i = 0;
    while (i < amount)
    {
        if ((pipex->opt_list)[i] != NULL) {
            close(((pipex->opt_list)[i])->fd[0]);
            close(((pipex->opt_list)[i])->fd[1]);
        }
        i++;
    }
}
