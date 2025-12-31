#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "feedback.h"
#include "libft.h"
#include "pipex.h"

static t_bool	parse_attr(t_pipex *pipex, char **argv, int argc);
static char	**parse_cmds(t_pipex *pipex, char **argv);
static t_bool parse_path(t_pipex *pipex);
static t_bool init_heredoc(t_pipex *pipex);

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
	if (!parse_path(pipex) || !parse_attr(pipex, argv, argc) || !init_heredoc(pipex))
	{
		free_pipex(pipex);
		return (NULL);
	}
	pipex->cmds = parse_cmds(pipex, argv);
	if (!pipex->cmds)
	{
		free_pipex(pipex);
		return (NULL);
	}
	return (pipex);
}

static t_bool	parse_attr(t_pipex *pipex, char **argv, int argc)
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
	return (TRUE);
}

static char	**parse_cmds(t_pipex *pipex, char **argv)
{
	char	**cmds;
	int		i;

	if (IS_BONUS && ft_strcmp(HEREDOC, argv[0]) == 0)
		argv += 2;
	else
		argv += 1;
	cmds = ft_calloc(pipex->cmd_count + 1, sizeof(char *));
	if (!cmds)
	{
		perror(ERROR);
		return (NULL);
	}
	i = -1;
	while (++i < pipex->cmd_count)
		cmds[i] = argv[i];
	return (cmds);
}

static t_bool parse_path(t_pipex *pipex)
{
	int i;
	int len;
	char *var;

	i = 0;
	len = ft_strlen(PATH);
	var = pipex->envp[0];
	while (var)
	{
		if (ft_strncmp(var, PATH, len) == 0)
		{
			var += len + 1;
			pipex->paths = ft_split(var, ':');
			if (!pipex->paths)
				return (error_msg(ERROR, TRUE));
			else
				return (TRUE);
		}
		var = pipex->envp[++i];
	}
	return (TRUE);
}

static t_bool init_heredoc(t_pipex *pipex)
{
	if (pipex->here_doc)
	{
		if (pipe(pipex->heredoc_fd) == -1)
			return (error_msg(ERROR, TRUE));
	}
	return (TRUE);
}
