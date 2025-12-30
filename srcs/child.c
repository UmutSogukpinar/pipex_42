#include <unistd.h>
#include <stdio.h>
#include "pipex.h"
#include "feedback.h"
#include "libft.h"

void execute_child(t_pipex *pipex, int i)
{
    char    **splitted_cmd;
    char    *cmd_first_element;

    splitted_cmd = ft_split(pipex->cmds[i], ' ');
    if (!splitted_cmd)
        exit(EXIT_FAILURE);
    cmd_first_element = ft_strdup(splitted_cmd[0]);
    if (!cmd_first_element)
        exit(EXIT_FAILURE);
    splitted_cmd[0] = get_full_cmd(pipex, splitted_cmd[0]);
    if (splitted_cmd[0] == NULL)
    {
        ft_putstr_fd(cmd_first_element, STDERR_FILENO);
        ft_putendl_fd(": command not found", STDERR_FILENO);
        exit(EXIT_CMD_NOT_FOUND);
    }
    free(cmd_first_element);
    execve(splitted_cmd[0], splitted_cmd, pipex->envp);
    perror(ERROR);
    exit(EXIT_FAILURE);
}

static char *get_full_cmd(t_pipex *pipex, char *old_cmd)
{
    char    *tmp;
    char    *full;
    int     i;

    if (!old_cmd || !*old_cmd)
        return (NULL);
    if (ft_strchr(old_cmd, '/'))
        return (old_cmd);
    i = -1;
    while (pipex->paths && pipex->paths[++i])
    {
        tmp = ft_strjoin(pipex->paths[i], "/");
        if (!tmp)
            exit(EXIT_FAILURE);
        full = ft_strjoin(tmp, old_cmd);
        free(tmp);
        if (!full)
            exit(EXIT_FAILURE);
        if (access(full, X_OK) == 0)
            return (free(old_cmd), full);
        free(full);
    }
    return (NULL);
}

