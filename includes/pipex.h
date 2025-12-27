#ifndef PIPEX_H
# define PIPEX_H

# ifndef IS_BONUS
#  define IS_BONUS 0
# endif

# define HEREDOC "here_doc"

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}			t_bool;

typedef struct s_pipex
{
	int		cmd_count;
	t_bool	here_doc;
	char	***cmds;
	char	**envp;
	char	*infile;
	char	*outfile;
	char	*limiter;
}			t_pipex;

t_pipex		*init_pipex(int argc, char **argv, char **envp);
int			ft_strcmp(const char *s1, const char *s2);
void		free_strv(char **v);
void		free_strvv(char ***vv);
void		free_pipex(t_pipex *pipex);

// ! to be removed
void		display_pipex(const t_pipex *px);

#endif