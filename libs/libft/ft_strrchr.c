/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:17:00 by umut              #+#    #+#             */
/*   Updated: 2024/12/10 20:17:01 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				index;
	unsigned char	new_c;

	new_c = (unsigned char) c;
	index = ft_strlen(s);
	if (s[index] == new_c)
		return ((char *) &s[index]);
	while (index >= 0)
	{
		if (s[index] == new_c)
			return ((char *)(s + index));
		index--;
	}
	return (NULL);
}
