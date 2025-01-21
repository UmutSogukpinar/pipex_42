/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:49:54 by usogukpi          #+#    #+#             */
/*   Updated: 2024/10/24 20:49:56 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*n_dest;
	unsigned char		*n_src;
	size_t				i;

	n_dest = (unsigned char *)dst;
	n_src = (unsigned char *)src;
	if (n_dest == n_src || len == 0)
		return (dst);
	if (n_dest < n_src)
	{
		i = 0;
		while (i < len)
		{
			n_dest[i] = n_src[i];
			i++;
		}
		return (dst);
	}
	i = len;
	while (i > 0)
	{
		n_dest[i - 1] = n_src[i - 1];
		i--;
	}
	return (dst);
}
