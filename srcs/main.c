/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:43:55 by umut              #+#    #+#             */
/*   Updated: 2025/01/15 19:38:49 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "pipex.h"
#include "ft_printf.h"

int	main(int arg_num, char **args, char **envp)
{
	t_pipex	*pipex;

	if (arg_num != 5)
		exit(EXIT_FAILURE);
	pipex = init_pipex(args, envp);
	display_pipex(pipex -> cmd_args, pipex -> paths);
	return (0);
}
