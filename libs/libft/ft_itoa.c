/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:13:44 by usogukpi          #+#    #+#             */
/*   Updated: 2024/10/24 20:13:46 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int static	ft_digit_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char static	*ft_itoa_negatives(int n, int digit_len)
{
	char	*arr;

	if (n == -2147483648)
	{
		return (ft_strdup("-2147483648"));
	}
	arr = malloc(digit_len + 1);
	if (!arr)
		return (NULL);
	n = -n;
	arr[digit_len] = '\0';
	arr[0] = '-';
	digit_len--;
	while (digit_len > 0)
	{
		arr[digit_len] = (n % 10) + '0';
		n /= 10;
		digit_len--;
	}
	return (arr);
}

char	*ft_itoa(int n)
{
	int		i;
	int		digit_len;
	char	*arr;

	digit_len = ft_digit_len(n);
	i = digit_len - 1;
	if (n < 0)
		return (ft_itoa_negatives(n, digit_len));
	arr = malloc(digit_len + 1);
	if (!arr)
		return (NULL);
	if (n == 0)
	{
		arr[0] = '0';
		arr[1] = '\0';
		return (arr);
	}
	arr[digit_len] = '\0';
	while (i >= 0)
	{
		arr[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (arr);
}
