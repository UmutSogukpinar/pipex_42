#include <unistd.h>
#include "pipex.h"

static void finalize_child(t_pipex *pipex, int i, int pipefd[2]);
static void setup_child_io(t_pipex *pipex, int i, int prev_fd, int pipefd[2]);

/**
 * Prepares the child process for command execution.
 *
 * - Sets up STDIN and STDOUT redirections
 * - Closes unused file descriptors
 * - Executes the resolved command
 *
 * This function does not return on success.
 *
 * @param pipex (t_pipex *): Pipex structure
 * @param i (int): Index of the command to execute
 * @param prev_fd (int): Read end of the previous pipe
 * @param pipefd (int[2]): Current pipe file descriptors
 */
void child_process(t_pipex *pipex, int i, int prev_fd, int pipefd[2])
{
    setup_child_io(pipex, i, prev_fd, pipefd);
    finalize_child(pipex, i, pipefd);
    execute_child(pipex, i);
}

/**
 * Configures input and output redirections for a child process.
 *
 * - STDIN:
 *   - infile or heredoc for the first command
 *   - previous pipe for subsequent commands
 *
 * - STDOUT:
 *   - outfile for the last command
 *   - write end of the current pipe otherwise
 *
 * @param pipex (t_pipex *): Pipex structure
 * @param i (int): Command index
 * @param prev_fd (int): Read end of the previous pipe
 * @param pipefd (int[2]): Current pipe file descriptors
 */
static void setup_child_io(t_pipex *pipex, int i, int prev_fd, int pipefd[2])
{
    if (i == 0)
    {
        init_infile(pipex);
        if (pipex->here_doc)
            dup2(pipex->heredoc_fd[READ_END], STDIN_FILENO);
        else
            dup2(pipex->fds.in_fd, STDIN_FILENO);
    }
    else
    {
        dup2(prev_fd, STDIN_FILENO);
        close_fd(&prev_fd);
    }
    if (i == pipex->cmd_count - 1)
    {
        init_outfile(pipex);
        dup2(pipex->fds.out_fd, STDOUT_FILENO);
    }
    else
        dup2(pipefd[WRITE_END], STDOUT_FILENO);
}

/**
 * finalize_child
 *
 * Closes all unused file descriptors in the child process
 * before command execution.
 *
 * Prevents file descriptor leaks and unintended inheritance.
 *
 * @param pipex (t_pipex *): Pipex structure
 * @param i (int): Command index
 * @param pipefd (int[2]): Current pipe file descriptors
 */
static void finalize_child(t_pipex *pipex, int i, int pipefd[2])
{
    if (i < pipex->cmd_count - 1)
    {
        close_fd(&(pipefd[READ_END]));
        close_fd(&(pipefd[WRITE_END]));
    }
    close_fd(&(pipex->fds.out_fd));
    if (pipex->here_doc)
        close_fd(&(pipex->heredoc_fd[READ_END]));
}
