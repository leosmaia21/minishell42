#include "execs.h"

char *ft_findpath(t_envp *head, char **envp, char **flags)
{
    char *p;
    char **split;
    char *cmd_path;

    p = ft_find_value(head, "PATH");
    split = ft_split(p, ':');
    while (split)
	{
		cmd_path = ft_strjoin(*split++, "/");
        cmd_path = ft_strjoin(cmd_path, flags[0]);
		if (!cmd_path)
            break ;
		if (!access(cmd_path, F_OK))
			return(cmd_path);
		free(cmd_path);
		cmd_path = NULL;
	}
    perror(strerror(errno));
    return(NULL);
}


void	ft_single_exec(char **flags, char **envp, char *path)
{
    if (ft_check_builtin(flags, envp) != 0)
    {
        if (path)
        {
            if (execve(path, flags, envp) == -1)
            perror("Error executing command");
        }
    }
}

int ft_count_command(t_token *tokens)
{
    int count;
    int i;

    i=-1;
    count = 0;
    while (++i < tokens[0].total)
    {
        if (tokens[i].type == command)
            count++;
    }
    return(count);
}

void setup_pipe(int input_fd, int output_fd)
{
    if (input_fd != STDIN_FILENO)
    {
        if (dup2(input_fd, STDIN_FILENO) == -1)
        {
            perror(strerror(errno));
            exit(EXIT_FAILURE);
        }
        close(input_fd);
    }

    if (output_fd != STDOUT_FILENO)
    {
        if (dup2(output_fd, STDOUT_FILENO) == -1)
        {
            perror(strerror(errno));
            exit(EXIT_FAILURE);
        }
        close(output_fd);
    }
}

void ft_main_exec(t_info *info)
{
    int pipes;
    int input_fd = STDIN_FILENO;
    int fd[2];
    int pid;
    char **flags;
    int i;

    i = -1;
    pipes = ft_count_command(info->tokens);
    if (pipe(fd) == -1)
        perror(strerror(errno));
    while (++i < pipes) {
        flags = jointokens(info->tokens, i);
        pid = fork();
        if (pid == -1)
            perror(strerror(errno));
        else if (pid == 0)
        {
            setup_pipe(input_fd, i < pipes - 1 ? fd[1] : STDOUT_FILENO);
            ft_single_exec(flags, info->envp, ft_findpath(info->tenv, info->envp, flags));
        }
        else
        {
            if (i < pipes - 1)
                close(fd[1]);
           waitpid(-1, &info->exit_code, 0);
            if (i < pipes - 1)
                input_fd = fd[0];
        }
    }
}