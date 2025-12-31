#include <stdlib.h>
#include "pipex.h"
#include "feedback.h"

static t_bool	is_args_valid(int argc, char **argv);

// Main Function
int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		exit_no;

	if (!is_args_valid(argc - 1, argv + 1))
		return (EXIT_FAILURE);
	pipex = init_pipex(argc - 1, argv + 1, envp);
	if (!pipex)
		return (EXIT_FAILURE);
	execute(pipex);
	exit_no = pipex->exit_no;
	free_pipex(pipex);
	return (exit_no);
}

/**
 * Validates command-line arguments count based on program mode.
 *
 * - In mandatory mode (IS_BONUS == FALSE):
 *   Expects exactly 4 arguments.
 *
 * - In bonus mode (IS_BONUS == TRUE):
 *   - If heredoc is used (argv[0] == HEREDOC):
 *     Expects at least 5 arguments.
 *   - Otherwise:
 *     Expects at least 4 arguments.
 *
 * On invalid argument count, prints an error message and returns FALSE.
 *
 * @param argc (int): Argument count
 * @param argv (char **): Argument vector
 * 
 * @return TRUE (t_bool): if arguments are valid, otherwise FALSE
 */
static t_bool	is_args_valid(int argc, char **argv)
{
	if (!IS_BONUS)
	{
		if (argc != 4)
			return (error_msg(ERR_INV_ARGC, FALSE));
	}
	else
	{
		if (ft_strcmp(argv[0], HEREDOC) == 0)
		{
			if (argc < 5)
				return (error_msg(ERR_INV_ARGC, FALSE));
		}
		else
		{
			if (argc < 4)
				return (error_msg(ERR_INV_ARGC, FALSE));
		}
	}
	return (TRUE);
}
