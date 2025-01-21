/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:50:54 by usogukpi          #+#    #+#             */
/*   Updated: 2024/10/24 20:50:56 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int static	ft_count_strings(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && (str[i] == c))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && !(str[i] == c))
			i++;
	}
	return (count);
}

void	*ft_free_word(char **strings, int string_amount)
{
	int	i;

	i = 0;
	while (i < string_amount)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
	return (NULL);
}

char static	*ft_get_word(char *str, char sep, int i)
{
	char	*word;
	int		start_index;
	int		word_index;
	int		len;

	start_index = i;
	word_index = 0;
	while (!(str[i] == sep) && str[i] != '\0')
		i++;
	len = i - start_index;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	while (word_index < len)
	{
		word[word_index] = str[start_index];
		start_index++;
		word_index++;
	}
	word[word_index] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	int		i;
	int		strings_index;

	strings_index = ft_count_strings((char *) s, c);
	strings = malloc(sizeof(char *) * (strings_index + 1));
	if (!strings)
		return (NULL);
	i = 0;
	strings_index = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && !(s[i] == c))
		{
			strings[strings_index++] = ft_get_word((char *) s, c, i);
			if (!strings[strings_index - 1])
				return (ft_free_word(strings, strings_index - 1));
		}
		while (s[i] != '\0' && !(s[i] == c))
			i++;
	}
	strings[strings_index] = NULL;
	return (strings);
}
