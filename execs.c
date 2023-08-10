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

#include "execs.h"

char	*ft_findpath(t_envp *head, char **flags)
{
	char	*p;
	char	**split;
	char	*cmd_path;
	char	*aux;
	char	**aux_split;

	if (!access(flags[0], F_OK))
			return (ft_strdup(flags[0]));
	p = ft_find_value(head, "PATH");
	split = ft_split(p, ':');
	aux_split = split;
	while (split)
	{
		aux = ft_strjoin(*split++, "/");
		cmd_path = ft_strjoin(aux, flags[0]);
		ft_freestr(aux);
		if (!cmd_path)
			break ;
		if (!access(cmd_path, F_OK))
		{
			ft_freedoublepointer(aux_split);
			return (cmd_path);
		}
		ft_freestr(cmd_path);
	}
	ft_freedoublepointer(aux_split);
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


void	first_process(int fd_pipe[2], char **flags, t_info *info, char *path)
{
	int		pid;

	if(ft_is_builtin(flags) != 0 || ft_count_command(info->tokens) > 1)
		pid = fork();
	else
		pid = 0;
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		close(fd_pipe[0]);
        if (ft_count_command(info->tokens) > 1)
		    dup2(fd_pipe[1], STDOUT_FILENO);
		if(ft_is_builtin(flags) != 0)
			execve(path, flags, info->envp);
		else
			ft_exec_builtin(flags, info, ft_count_command(info->tokens) > 1);
	}
	if(ft_count_command(info->tokens) > 1)
		close(fd_pipe[1]);
	waitpid(pid, &info->exit_code, 0);
}

void	second_process(int fd_pipe[2], char **flags, t_info *info, char *path)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		
		dup2(STDOUT_FILENO, fd_pipe[1]);
		close(fd_pipe[1]);
		if(ft_is_builtin(flags) != 0)
		{
			dup2(fd_pipe[0], STDIN_FILENO);
			execve(path, flags, info->envp);
		}
		else
			ft_exec_builtin(flags, info, 0);
	}
	close(fd_pipe[0]);
	waitpid(pid, &info->exit_code, 0);
}


void	midle_process(int	fd_pipe[2], char	**flags, t_info *info,char	*path)
{
	int	pid;
	int temp_fd[2];

	close(fd_pipe[1]);
	if (pipe(temp_fd) == -1)
		perror(strerror(errno));
	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		close(temp_fd[0]);
		close(fd_pipe[1]);
		dup2(temp_fd[1], STDOUT_FILENO);
		if(ft_is_builtin(flags) != 0)
		{
			dup2(fd_pipe[0], STDIN_FILENO);
			execve(path, flags, info->envp);
		}	
		else
			ft_exec_builtin(flags, info, ft_count_command(info->tokens) > 1);
	}
	waitpid(pid, &info->exit_code, 0);
	dup2(temp_fd[0], fd_pipe[0]);
	close(temp_fd[1]);
	close(temp_fd[0]);
}


void	ft_main_exec(t_info *info)
{
	int		pipes;
	int		fd[2];
	char	**flags;
	char	*path;
	int 	i;

	i = -1;
	pipes = ft_count_command(info->tokens);
	if (pipe(fd) == -1)
		perror(strerror(errno));
	while (++i < pipes) 
    {
		flags = jointokens(info->tokens, i);
		path = ft_findpath(info->tenv, flags);
        if ((path != NULL) || ft_is_builtin(flags) == 0)
		{
			if (i == 0)
				first_process(fd, flags, info, path);
			else if (i == pipes - 1)
				second_process(fd, flags, info, path);
			else
				midle_process(fd, flags, info, path);
		}
		else
			perror(flags[0]);
		if (path)
			free(path);
		ft_freedoublepointer(flags);
	}
}


