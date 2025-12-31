#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"
#include "get_next_line.h"

static void prepare_heredoc(t_pipex *pipex);
static void parent_process(int i, int count, int *prev_fd, int pipefd[2]);
static void wait_all(t_pipex *pipex, int count, pid_t last_pid);

/**
 * Executes all commands using pipes and forks.
 *
 * - Prepares heredoc input if enabled
 * - Creates pipes between commands
 * - Forks a process for each command
 * - Manages parent/child responsibilities
 * - Waits for all children and stores last command exit code
 *
 * @param pipex (t_pipex *): Initialized pipex structure
 */
void execute(t_pipex *pipex)
{
    int     i;
    int     prev_fd;
    int     pipefd[2];
    pid_t   pid;

    prev_fd = -1;
    i = 0;
    if (pipex->here_doc)
        prepare_heredoc(pipex);
    while (i < pipex->cmd_count)
    {
        if (i < pipex->cmd_count - 1 && pipe(pipefd) == -1)
            exit_error(pipex);
        pid = fork();
        if (pid == -1)
            exit_error(pipex);
        if (pid == 0)
            child_process(pipex, i, prev_fd, pipefd);
        parent_process(i, pipex->cmd_count, &prev_fd, pipefd);
        i++;
    }
    wait_all(pipex, pipex->cmd_count, pid);
}

/**
 * Handles file descriptor management in the parent process.
 *
 * - Closes previous pipe read end
 * - Prepares next command input by storing current pipe read end
 *
 * @param i (int): Current command index
 * @param count (int):  Total command count
 * @param prev_fd (int *): Pointer to previous pipe read end
 * @param pipefd (int[2]): Current pipe file descriptors
 */
static void parent_process(int i, int count, int *prev_fd, int pipefd[2])
{
    if (*prev_fd != -1)
        close_fd(prev_fd);
    if (i < count - 1)
    {
        close_fd(&(pipefd[WRITE_END]));
        *prev_fd = pipefd[READ_END];
    }
}

/**
 * Waits for all child processes to terminate.
 *
 * Captures the exit status of the last executed command,
 * following shell behavior.
 *
 * - Normal exit: exit code
 * - Signal exit: 128 + signal number
 *
 * @param pipex (t_pipex *): Pipex structure to store exit code
 * @param count (int): Number of child processes
 * @param last_pid (pid_t): PID of the last command
 */
static void wait_all(t_pipex *pipex, int count, pid_t last_pid)
{
    int     status;
    pid_t   pid;
    int     i;

    i = 0;
    while (i < count)
    {
        pid = wait(&status);
        if (pid == -1)
            break;
        if (pid == last_pid)
        {
            if (WIFEXITED(status))
                pipex->exit_no = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                pipex->exit_no = 128 + WTERMSIG(status);
        }
        i++;
    }
}

/**
 * Reads input from STDIN until the limiter is encountered
 * and writes it to the heredoc pipe.
 *
 * The write end of the heredoc pipe is closed after completion.
 *
 * @param pipex (t_pipex *): Pipex structure containing heredoc data
 */
static void prepare_heredoc(t_pipex *pipex)
{
    char *line;

	line = get_next_line(STDIN_FILENO);
    while (line)
    {
        if (!ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter))
            && line[ft_strlen(pipex->limiter)] == '\n')
        {
            free(line);
            break;
        }
        write(pipex->heredoc_fd[WRITE_END], line, ft_strlen(line));
        free(line);
		line = get_next_line(STDIN_FILENO);
    }
	free_gnl();
    close_fd(&(pipex->heredoc_fd[WRITE_END]));
}
