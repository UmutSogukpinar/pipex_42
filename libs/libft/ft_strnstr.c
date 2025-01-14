/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:16:56 by umut              #+#    #+#             */
/*   Updated: 2024/12/10 20:16:57 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n_i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		n_i = 0;
		while ((haystack[i + n_i] == needle[n_i]) && (i + n_i < len))
		{
			if (n_i == needle_len - 1)
				return ((char *)&haystack[i]);
			n_i++;
		}
		i++;
	}
	return (NULL);
}
