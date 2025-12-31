#include <unistd.h>
#include <stdio.h>
#include "pipex.h"
#include "libft.h"

/**
 * Compares two null-terminated strings lexicographically.
 *
 * Returns the difference between the first differing characters
 * casted to unsigned char.
 *
 * @param s1 (const char *): First string
 * @param s2 (const char *): Second string
 * 
 * @return (int):  An integer less than, equal to, or greater than zero
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/**
 * Prints an error message to STDERR.
 *
 * If is_perror is TRUE, uses perror with the given message.
 * Otherwise, prints a custom error message prefixed with "[ERROR]:".
 *
 * Always returns FALSE to allow direct usage in return statements.
 *
 * @param msg (char *): Error message
 * @param is_perror (t_bool): Flag to use perror or custom message
 * 
 * @return (t_bool): FALSE
 */
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

/**
 * Safely closes a file descriptor if it is valid.
 *
 * After closing, sets the file descriptor value to CLOSED_FD (-1)
 * to prevent accidental reuse.
 *
 * @param fd (int *): Pointer to the file descriptor
 */
void	close_fd(int *fd)
{
	if (*fd > 0)
		close(*fd);
	*fd = CLOSED_FD;
}
