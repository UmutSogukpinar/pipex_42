/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:54:07 by usogukpi          #+#    #+#             */
/*   Updated: 2024/10/27 13:02:21 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_print_char(va_list args)
{
	ft_put_char((char) va_arg(args, int));
	return (1);
}

int	ft_str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*ft_str_dup(char *s1)
{
	int		i;
	int		len;
	char	*new;

	if (!s1)
		return (NULL);
	len = ft_str_len(s1);
	new = malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_print_str(va_list args)
{
	char	*str;
	int		str_len;

	str = ft_str_dup(va_arg(args, char *));
	str_len = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[str_len] != '\0')
	{
		ft_put_char(str[str_len]);
		str_len++;
	}
	free(str);
	return (str_len);
}
