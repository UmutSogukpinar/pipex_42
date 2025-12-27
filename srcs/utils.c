#include "pipex.h"
#include "stdlib.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	free_strv(char **v)
{
	size_t	i;

	if (!v)
		return ;
	i = 0;
	while (v[i])
	{
		free(v[i]);
		i++;
	}
	free(v);
}

void	free_strvv(char ***vv)
{
	size_t	i;

	if (!vv)
		return ;
	i = 0;
	while (vv[i])
	{
		free_strv(vv[i]);
		i++;
	}
	free(vv);
}

void	free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	free_strvv(pipex->cmds);
	free(pipex);
}

// ! for debug (to be removed)

#include "stdio.h"

void	display_pipex(const t_pipex *px)
{
	int	i;
	int	j;

	if (!px)
	{
		printf("[PIPEX] NULL struct\n");
		return ;
	}
	printf("========== PIPEX STATE ==========\n");
	printf("cmd_count : %d\n", px->cmd_count);
	printf("here_doc  : %s\n", px->here_doc ? "TRUE" : "FALSE");
	printf("infile   : %s\n", px->infile ? px->infile : "(null)");
	printf("outfile  : %s\n", px->outfile ? px->outfile : "(null)");
	printf("limiter  : %s\n", px->limiter ? px->limiter : "(null)");
	printf("\ncommands:\n");
	i = 0;
	while (px->cmds && px->cmds[i])
	{
		printf("  cmd[%d]: ", i);
		j = 0;
		while (px->cmds[i][j])
		{
			printf("[%s] ", px->cmds[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("=================================\n");
}
