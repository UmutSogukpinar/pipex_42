#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "pipex.h"
#include "feedback.h"

static t_bool	parse_attr(t_pipex *pipex, char **argv, int argc);
static char	**parse_cmds(t_pipex *pipex, char **argv);
static t_bool parse_path(t_pipex *pipex);
static t_bool init_heredoc(t_pipex *pipex);

/**
 * Allocates and initializes the main pipex structure.
 *
 * - Stores envp reference
 * 
 * - Sets output file
 * 
 * - Parses PATH variable
 * 
 * - Parses program attributes (heredoc, infile, command count)
 * 
 * - Initializes heredoc pipe if needed
 * 
 * - Extracts command list
 *
 * On any failure, frees allocated resources and returns NULL.
 *
 * @param argc (int): Argument count
 * @param argv (char **): Argument vector
 * @param envp (char **): Environment variables
 * 
 * @return (t_pipex *): Initialized t_pipex pointer or NULL on error
 */
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

/**
 * Parses execution attributes from command-line arguments.
 *
 * - In bonus + heredoc mode:
 *   Sets heredoc flag, limiter, and command count.
 *
 * - Otherwise:
 *   Sets infile and command count for normal execution.
 *
 * @param pipex (t_pipex): Pipex structure to fill
 * @param argv (char **): Argument vector
 * @param argc (int): Argument count
 * 
 * @return (t_bool): TRUE always (attributes are derived, not validated)
 */
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

/**
 * Extracts command strings from argument list and stores them
 * in a NULL-terminated array.
 *
 * Adjusts argv offset depending on heredoc usage.
 *
 * @param pipex (t_pipex *): Initialized pipex structure
 * @param argv (char **): Argument vector
 * 
 * @return (char **): Array of command strings or NULL on allocation failure
 */
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

/**
 * Searches for PATH variable in environment and splits it into
 * individual directories.
 *
 * If PATH is not found, execution continues without path resolution.
 *
 * @param pipex (t_pipex *): Initialized pipex structure
 * 
 * @return (t_bool): TRUE on success, FALSE on split failure
 */

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

/**
 * Initializes heredoc pipe if heredoc mode is enabled.
 *
 * @param (t_pipex *): pipex Pipex structure
 * 
 * @return (t_bool): TRUE on success, FALSE if pipe creation fails
 */

static t_bool init_heredoc(t_pipex *pipex)
{
	if (pipex->here_doc)
	{
		if (pipe(pipex->heredoc_fd) == -1)
			return (error_msg(ERROR, TRUE));
	}
	return (TRUE);
}
