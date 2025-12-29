#include "pipex.h"
#include "stdlib.h"

// TODO: could turn into static !!!
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

void	free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	free_strv(pipex->paths);
	free(pipex->cmds);
	free(pipex);
}
