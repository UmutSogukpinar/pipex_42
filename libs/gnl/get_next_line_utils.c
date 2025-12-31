#include "get_next_line.h"

int	ft_is_newline_char(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new_str;

	new_str = (char *) malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = s[start + i];
		i++;
	}
	new_str[len] = '\0';
	return (new_str);
}

char	*ft_update_repo(char *total_line, char *repo)
{
	size_t	repo_len;
	size_t	line_len;

	repo_len = ft_strlen(repo);
	line_len = ft_strlen(total_line);
	return (ft_substr2(repo, line_len, repo_len - line_len));
}

void free_gnl()
{
    get_next_line(-1);
}
