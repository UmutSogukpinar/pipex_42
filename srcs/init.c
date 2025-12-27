#include "feedback.h"
#include "libft.h"
#include "pipex.h"
#include <stdio.h>

static void	parse_attr(t_pipex *pipex, char **argv, int argc);
static char	***parse_cmds(t_pipex *pipex, char **argv);
static char	**parse_each_cmd(char *arg);

t_pipex	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
	{
		perror(ERROR);
		return (NULL);
	}
	pipex->envp = envp;
	pipex->outfile = argv[argc - 1];
	parse_attr(pipex, argv, argc);
	pipex->cmds = parse_cmds(pipex, argv);
	if (!pipex->cmds)
	{
		free(pipex);
		return (NULL);
	}
	return (pipex);
}

static void	parse_attr(t_pipex *pipex, char **argv, int argc)
{
	if (IS_BONUS && ft_strcmp(HEREDOC, argv[0]) == 0)
	{
		pipex->here_doc = TRUE;
		pipex->cmd_count = argc - 3;
		pipex->limiter = argv[1];
	}
	else
	{
		pipex->here_doc = FALSE;
		pipex->cmd_count = argc - 2;
		pipex->infile = argv[0];
	}
}

static char	***parse_cmds(t_pipex *pipex, char **argv)
{
	char	***cmds;
	int		i;

	if (IS_BONUS && ft_strcmp(HEREDOC, argv[0]) == 0)
		argv += 2;
	else
		argv += 1;
	cmds = ft_calloc(pipex->cmd_count + 1, sizeof(char **));
	if (!cmds)
	{
		perror(ERROR);
		return (NULL);
	}
	i = -1;
	while (++i < pipex->cmd_count)
	{
		cmds[i] = parse_each_cmd(argv[i]);
		if (!cmds[i])
		{
			free_strvv(cmds);
			return (NULL);
		}
	}
	return (cmds);
}

static char	**parse_each_cmd(char *arg)
{
	char	**cmd;

	cmd = ft_split(arg, ' ');
	if (!cmd)
	{
		perror(ERROR);
		return (NULL);
	}
	return (cmd);
}
