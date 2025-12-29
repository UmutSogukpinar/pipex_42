#include <unistd.h>
#include <stdio.h>
#include "pipex.h"
#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

t_bool	error_msg(char *msg, t_bool is_perror)
{
	if (is_perror)
	{
		perror(msg);
	}
	else
	{
		ft_putstr_fd("[ERROR]: ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	return (FALSE);
}

// ! for debug (to be removed)

#include "stdio.h"

static void	display_str_array(const char *name, char **arr)
{
	int	i;

	printf("%s:\n", name);
	if (!arr)
	{
		printf("  (null)\n");
		return;
	}
	i = 0;
	while (arr[i])
	{
		printf("  [%d] %s\n", i, arr[i]);
		i++;
	}
}

void	display_pipex(const t_pipex *p)
{
	if (!p)
	{
		printf("pipex: (null)\n");
		return;
	}

	printf("===== PIPEX STATE =====\n");
	printf("cmd_count : %d\n", p->cmd_count);
	printf("here_doc  : %s\n", p->here_doc == TRUE ? "TRUE" : "FALSE");

	printf("fds:\n");
	printf("  in_fd  : %d\n", p->fds.in_fd);
	printf("  out_fd : %d\n", p->fds.out_fd);

	printf("infile  : %s\n", p->infile ? p->infile : "(null)");
	printf("outfile : %s\n", p->outfile ? p->outfile : "(null)");
	printf("limiter : %s\n", p->limiter ? p->limiter : "(null)");

	display_str_array("cmds", p->cmds);
	display_str_array("paths", p->paths);

	printf("=======================\n");
}
