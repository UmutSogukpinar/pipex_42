#include "feedback.h"
#include "libft.h"
#include "pipex.h"
#include "unistd.h"

static t_bool	is_args_valid(int argc, char **argv);

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
