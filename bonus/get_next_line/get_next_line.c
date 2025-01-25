/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:49:21 by usogukpi          #+#    #+#             */
/*   Updated: 2025/01/25 16:07:23 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include "libft.h"

int	ft_set_d(char **data)
{
	if (!data)
		return (1);
	if (*data == NULL)
	{
		*data = (char *) malloc(sizeof(char));
		if (*data)
			**data = '\0';
		else
			return (1);
	}
	return (0);
}

char	*ft_free_and_update_repo(char **old, char *new)
{
	if (*old)
		free(*old);
	*old = new;
	return (new);
}

char	*ft_free_and_clean(char **data)
{
	if (*data)
	{
		free(*data);
		*data = NULL;
	}
	return (NULL);
}

char	*ft_get_the_line(char *data)
{
	size_t	len;

	if (!data)
		return (NULL);
	len = 0;
	while (data[len] != '\0')
	{
		if (data[len] == '\n')
		{
			len++;
			break ;
		}
		len++;
	}
	return (ft_substr(data, 0, len));
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*repo = NULL;
	char		*total_line;
	int			bytes_read;

	if (fd < 0 || ft_set_d(&repo) || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 0;
	while (repo && !ft_is_newline_char(repo))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		ft_free_and_update_repo(&repo, ft_strjoin(repo, buffer));
	}
	if (!repo)
		return (ft_free_and_clean(&repo));
	if (bytes_read == -1 || repo[0] == '\0')
		return (ft_free_and_clean(&repo));
	total_line = ft_get_the_line(repo);
	if (!total_line)
		return (ft_free_and_clean(&repo));
	ft_free_and_update_repo(&repo, ft_update_repo(total_line, repo));
	return (total_line);
}
