/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:16:17 by umut              #+#    #+#             */
/*   Updated: 2024/12/10 20:16:18 by umut             ###   ########.fr       */
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
