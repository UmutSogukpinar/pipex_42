/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:17:54 by umut              #+#    #+#             */
/*   Updated: 2024/12/10 20:26:56 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HELPERS_H
# define FT_HELPERS_H

# include <stdarg.h>

int		ft_put_char(char c);
int		ft_str_len(char *str);
int		ft_print_char(va_list args);
int		ft_print_str(va_list args);

int		ft_print_int(va_list args, char *base);
int		ft_print_uns(va_list args, char *base);

int		ft_print_adress(va_list args, char *base);

#endif