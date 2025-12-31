#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "pipex.h"
#include "feedback.h"

static char *get_full_cmd(t_pipex *pipex, char *old_cmd);
static char **split_and_validate_cmd(t_pipex *pipex, int i);
static void resolve_command_path(t_pipex *pipex, char **cmd);
static void exec_command(t_pipex *pipex, char **cmd);

/**
 * Resolves and executes a single command in the child process.
 *
 * - Splits and validates command arguments
 * - Resolves executable path
 * - Executes command using execve
 *
 * @param pipex (t_pipex *): Pipex structure
 * @param i (int): Index of the command to execute
 */
void execute_child(t_pipex *pipex, int i)
{
    char **cmd;

    cmd = split_and_validate_cmd(pipex, i);
    resolve_command_path(pipex, cmd);
    exec_command(pipex, cmd);
}

/**
 * Resolves the full executable path of a command.
 *
 * - If the command contains '/', it is treated as a direct path
 * - Otherwise, searches through PATH directories
 *
 * On success, returns a newly allocated full path.
 * On failure, frees old_cmd and returns NULL.
 *
 * @param pipex (t_pipex): Pipex structure
 * @param old_cmd (char *): Command name
 * 
 * @return (char *): Full command path or NULL if not found
 */
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

/**
 * Splits a command string into arguments and validates it.
 *
 * If the command is empty, prints an error message and exits
 * with command-not-found status.
 *
 * @param pipex (t_pipex *): Pipex structure
 * @param i (int): Command index
 * 
 * @return (char **): NULL-terminated argument vector
 */
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

/**
 * resolve_command_path
 *
 * Resolves the executable path of the command.
 *
 * Replaces cmd[0] with the resolved full path.
 * If resolution fails, prints an error message and exits
 * with command-not-found status.
 *
 * @param pipex (t_pipex): Pipex structure
 * @param cmd (char **): Argument vector
 */
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

/**
 * Executes a command using execve.
 *
 * On failure, prints a system error and exits the program.
 *
 * @param pipex (t_pipex *): Pipex structure
 * @param cmd (char **): Argument vector
 */
static void exec_command(t_pipex *pipex, char **cmd)
{
    execve(cmd[0], cmd, pipex->envp);
    perror(ERROR);
    exit_error(pipex);
}
