#ifndef PIPEX_H
# define PIPEX_H

# ifndef IS_BONUS
#  define IS_BONUS 0
# endif

# define HEREDOC "here_doc"
# define PATH "PATH="

# define CLOSED_FD -1

# define READ_END 0
# define WRITE_END 1

# define EXIT_CMD_NOT_FOUND 127

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}			t_bool;

typedef struct s_fds
{
	int in_fd;
	int out_fd;
}				t_fds;


typedef struct s_pipex
{
	int		exit_no;
	int		cmd_count;
	t_bool	here_doc;
	int		heredoc_fd[2];
	t_fds	fds;
	char	**cmds;
	char	**envp;
	char	**paths;
	char	*infile;
	char	*outfile;
	char	*limiter;
}			t_pipex;


t_pipex		*init_pipex(int argc, char **argv, char **envp);
void execute_child(t_pipex *pipex, int i);
int			ft_strcmp(const char *s1, const char *s2);
void		free_strv(char **v);
void		free_pipex(t_pipex *pipex);
t_bool		error_msg(char *msg, t_bool is_perror);
void		exit_error(t_pipex *pipex);

// ! to be removed
void		display_pipex(const t_pipex *p);

#endif