/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 execs.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: ledos-sa <ledos-sa@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2023/08/02 13:01:58 by ledos-sa		   #+#	  #+#			  */
/*	 Updated: 2023/08/02 13:02:00 by ledos-sa		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <sys/wait.h>
#include "execs.h"

char	*ft_findpath(t_envp *head, char **flags)
{
	char	*p;
	char	**split;
	char	*cmd_path;

	p = ft_find_value(head, "PATH");
	split = ft_split(p, ':');
	while (split)
	{
		cmd_path = ft_strjoin(*split++, "/");
		cmd_path = ft_strjoin(cmd_path, flags[0]);
		if (!cmd_path)
			break ;
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
	}
	perror(strerror(errno));
	return (NULL);
}

int	ft_count_command(t_token *tokens)
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

// void	ft_single_exec(char **flags, t_info *info, char *path)
// {
// 	if (path)
// 	{
// 		if (execve(path, flags, info ->envp) == -1)
// 			perror("Error executing command");
// 	}

// }


void	first_process(int fd_pipe[2], char **flags, t_info *info, char *path)
{
	int		pid;
	
	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		close(fd_pipe[0]);
        if (ft_count_command(info->tokens) > 1)
		    dup2(fd_pipe[1], STDOUT_FILENO);
		execve(path, flags, info->envp);
	}
    else
    {
		close(fd_pipe[1]);
	    waitpid(pid, &info->exit_code, 0);
	    ft_freedoublepointer(flags);
    }
}

void	second_process(int fd_pipe[2], char **flags, t_info *info, char *path)
{
	int		pid;
	
	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		close(fd_pipe[1]);
		//dup2(fd_pipe[0], STDIN_FILENO);
		execve(path, flags, info->envp);
	}
    else
    {
		close(fd_pipe[0]);
	    waitpid(pid, &info->exit_code, 0);
	    ft_freedoublepointer(flags);
    }
}

void	ft_main_exec(t_info *info)
{
	int		pipes;
	int		fd[2];
	char	**flags;
	int 	i;

	i = -1;
	pipes = ft_count_command(info->tokens);
	if (pipe(fd) == -1)
		perror(strerror(errno));
	while (++i < pipes) 
    {
		flags = jointokens(info->tokens, i);
        if(ft_is_builtin(flags) != 0)
        {
            if (ft_findpath(info->tenv, flags) != NULL)
            {
                if (i == 0)
                    first_process(fd, flags, info, ft_findpath(info->tenv, flags));
                else
                    second_process(fd, flags, info, ft_findpath(info->tenv, flags));
            }
        }
        else
        {
            if (pipes - 1 - i > 0)
            {
                dup2(fd[0], STDOUT_FILENO); 
                //close(fd[0]);
            }   
            ft_check_builtin(flags, info->envp, info->tenv);
        }
	}
    close(fd[0]);
    close(fd[1]);
}


