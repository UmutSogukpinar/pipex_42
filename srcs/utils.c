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

void	close_fd(int *fd)
{
	if (*fd > 0)
		close(*fd);
	*fd = CLOSED_FD;
}
