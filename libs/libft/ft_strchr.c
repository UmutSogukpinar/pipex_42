/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:51:00 by usogukpi          #+#    #+#             */
/*   Updated: 2024/10/24 20:51:02 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	new_c;

	i = 0;
	new_c = (unsigned char) c;
	while (s[i] != '\0')
	{
		if (s[i] == new_c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == new_c)
		return ((char *) &s[i]);
	else
		return (NULL);
}
