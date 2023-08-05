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

void	ft_single_exec(char **flags, t_info *info, char *path)
{
    if (ft_check_builtin(flags, info->envp, info->tenv) != 0)
    {
        if (path)
        {
            if (execve(path, flags, info ->envp) == -1)
            perror("Error executing command");
        }
    }
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

void	setup_pipe(int input_fd, int output_fd)
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

void ft_exec_pipes(t_info *info, int *input_fd, int *fd, int i)
{
	int		pid;
	char	**flags;
	int		pipes;

	pipes = ft_count_command(info->tokens);
	flags = jointokens(info->tokens, i);
	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	else if (pid == 0)
	{
		setup_pipe(*input_fd, i < pipes - 1 ? fd[1] : STDOUT_FILENO);
		ft_single_exec(flags, info, ft_findpath(info->tenv, flags));
	}
	else
	{
		if (i < pipes - 1)
			close(fd[1]);
		waitpid(-1, &info->exit_code, 0);
		if (i < pipes - 1)
			input_fd = &fd[0];
	}
}

void	ft_main_exec(t_info *info)
{
	int		pipes;
	int		input_fd = STDIN_FILENO;
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
				ft_exec_pipes(info, &input_fd, fd, i);
		}
		else
		{
			setup_pipe(input_fd, i < pipes - 1 ? fd[1] : STDOUT_FILENO);
			ft_check_builtin(flags, info->envp, info->tenv);
		}
	}
}
