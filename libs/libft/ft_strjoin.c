/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:51:22 by usogukpi          #+#    #+#             */
/*   Updated: 2024/10/24 20:51:24 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*arr;
	size_t	i;
	size_t	arr_index;

	i = 0;
	arr_index = 0;
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	arr = malloc(total_size);
	if (arr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		arr[arr_index++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		arr[arr_index++] = s2[i];
		i++;
	}
	arr[arr_index] = '\0';
	return (arr);
}
