/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:55:17 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/25 16:09:56 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "get_next_line.h"
#include "libft.h"
#include "unistd.h"

static char	*update_wo_newline(char *str);

void	here_doc_input(char **args, int fd[])
{
	char	*limiter;
	char	*input;
	char	*updated_input;

	limiter = args[2];
	while (1)
	{
		close(fd[0]);
		input = get_next_line(0);
		if (input == NULL)
		{
			close(fd[1]);
			return ;
		}
		updated_input = update_wo_newline(input);
        if (!updated_input)
        
		if (is_strs_equals(limiter, input))
		{
			close(fd[1]);
			free(input);
			return ;
		}
		ft_putstr_fd(input, fd[1]);
	}
}

void	here_doc_output(char **args, int fd[], char **envp)
{
}

static char	*update_wo_newline(char *str)
{
	int		i;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	if (ft_is_newline_char(str))
		new = malloc(sizeof(char) * (ft_strlen(str)));
	else
		new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
