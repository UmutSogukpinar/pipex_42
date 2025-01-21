/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:52:12 by usogukpi          #+#    #+#             */
/*   Updated: 2024/10/24 20:52:15 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int static	ft_is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int static	ft_trimlen(char const *s1, char const *set)
{
	int	j;
	int	counter;
	int	total_len;

	counter = 0;
	total_len = ft_strlen(s1);
	j = total_len - 1;
	while (s1[counter] != '\0' && ft_is_set(s1[counter], set))
	{
		counter++;
		if (s1[counter] == '\0')
			return (0);
	}
	while (j >= 0 && ft_is_set(s1[j], set))
	{
		counter++;
		j--;
	}
	return (total_len - counter);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*arr;
	int		len;
	int		i;
	int		j;

	len = ft_trimlen(s1, set);
	arr = malloc(len + 1);
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0' && ft_is_set(s1[i], set))
		i++;
	while (j < len)
	{
		arr[j] = s1[i];
		i++;
		j++;
	}
	arr[len] = '\0';
	return (arr);
}
