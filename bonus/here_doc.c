/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:55:17 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/27 00:07:21 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "get_next_line.h"
#include "libft.h"
#include "unistd.h"
#include "fcntl.h"

static char	*update_w_newline(char *str);
static void	free_both(char *s1, char *s2);

void	here_doc_input(char **args, int fd[])
{
	char	*limiter;
	char	*input;

	limiter = update_w_newline(args[2]);
	if (!limiter)
		exit(EXIT_FAILURE);
	close(fd[0]);
	while (1)
	{
		input = get_next_line(0);
		if (!input || is_strs_equals(limiter, input))
		{
			close(fd[1]);
			free_both(limiter, input);
			return ;
		}
		ft_putstr_fd(input, fd[1]);
		free_data(input);
	}
}

void	here_doc_output(char **args, int fd[], char **envp)
{
	int	outfile_fd;

	outfile_fd = open(args[5], O_CREAT | O_APPEND | O_RDWR);
	if (outfile_fd < 0)
		exit(EXIT_FAILURE);
	if (dup2(outfile_fd, STDOUT_FILENO) < 0)
	{
		close(outfile_fd);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[0], STDIN_FILENO) < 0)
	{
		close(outfile_fd);
		exit(EXIT_FAILURE);
	}
	close(outfile_fd);
	close(fd[1]);
	close(fd[0]);
	
}

static char	*update_w_newline(char *str)
{
	int		i;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = '\n';
	new[i] = '\0';
	return (new);
}

static void	free_both(char *s1, char *s2)
{
	free_data(s1);
	free_data(s2);
}
