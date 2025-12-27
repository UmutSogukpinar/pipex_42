#include "feedback.h"
#include "libft.h"
#include "pipex.h"
#include "unistd.h"

static t_bool	is_args_valid(int argc, char **argv);
static t_bool	error_msg(char *msg);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (!is_args_valid(argc - 1, argv + 1))
		return (EXIT_FAILURE);
	pipex = init_pipex(argc - 1, argv + 1, envp);
	if (!pipex)
		return (EXIT_FAILURE);
	display_pipex(pipex);
	free_pipex(pipex);
	return (EXIT_SUCCESS);
}

static t_bool	is_args_valid(int argc, char **argv)
{
	if (!IS_BONUS)
	{
		if (argc != 4)
			return (error_msg(INV_ARGC));
	}
	else
	{
		if (ft_strcmp(argv[0], HEREDOC) == 0)
		{
			if (argc < 5)
				return (error_msg(INV_ARGC));
		}
		else
		{
			if (argc < 4)
				return (error_msg(INV_ARGC));
		}
	}
	return (TRUE);
}

static t_bool	error_msg(char *msg)
{
	ft_putstr_fd("[ERROR]: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (FALSE);
}
