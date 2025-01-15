/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:43:55 by umut              #+#    #+#             */
/*   Updated: 2025/01/15 18:00:48 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "pipex.h"

int	main(int arg_num, char **args, char **envp)
{
	t_pipex	*pipex;

	if (arg_num != 5)
		exit(EXIT_FAILURE);
	pipex = init_pipex(args);
	return (0);
}
