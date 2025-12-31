#include <unistd.h>
#include <stdio.h>
#include "pipex.h"
#include "feedback.h"
#include "libft.h"

static char *get_full_cmd(t_pipex *pipex, char *old_cmd);
static char **split_and_validate_cmd(t_pipex *pipex, int i);
static void resolve_command_path(t_pipex *pipex, char **cmd);
static void exec_command(t_pipex *pipex, char **cmd);

void execute_child(t_pipex *pipex, int i)
{
    char **cmd;

    cmd = split_and_validate_cmd(pipex, i);
    resolve_command_path(pipex, cmd);
    exec_command(pipex, cmd);
}

static char *get_full_cmd(t_pipex *pipex, char *old_cmd)
{
    char    *tmp;
    char    *full;
    int     i;

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
    free(old_cmd);
    return (NULL);
}

static char **split_and_validate_cmd(t_pipex *pipex, int i)
{
    char **cmd;

    cmd = ft_split(pipex->cmds[i], ' ');
    if (!cmd)
        exit_error(pipex);
    if (!cmd[0])
    {
        ft_putstr_fd(pipex->cmds[i], STDERR_FILENO);
        ft_putendl_fd(": command not found", STDERR_FILENO);
        free_strv(cmd);
        free_pipex(pipex);
        exit(EXIT_CMD_NOT_FOUND);
    }
    return (cmd);
}

static void resolve_command_path(t_pipex *pipex, char **cmd)
{
    char *cmd_name;

    cmd_name = ft_strdup(cmd[0]);
    if (!cmd_name)
    {
        free_strv(cmd);
        exit_error(pipex);
    }
    cmd[0] = get_full_cmd(pipex, cmd[0]);
    if (!cmd[0])
    {
        ft_putstr_fd(cmd_name, STDERR_FILENO);
        ft_putendl_fd(": command not found", STDERR_FILENO);
        free(cmd_name);
        free_strv(cmd);
        free_pipex(pipex);
        exit(EXIT_CMD_NOT_FOUND);
    }
    free(cmd_name);
}

static void exec_command(t_pipex *pipex, char **cmd)
{
    execve(cmd[0], cmd, pipex->envp);
    perror(ERROR);
    exit_error(pipex);
}

