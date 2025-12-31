#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
# endif

# include "../libft/libft.h"

char	*get_next_line(int fd);
void    free_gnl();
int		ft_is_newline_char(const char *s);
char	*ft_update_repo(char *total_line, char *repo);
char	*ft_substr2(char const *s, unsigned int start, size_t len);

#endif