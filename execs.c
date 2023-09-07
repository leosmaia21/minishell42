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
	int		ft_stdout;

	ft_stdout = ft_output_fd(info->tokens, info->ordem, STDOUT_FILENO);
	if(ft_is_builtin(flags) != 0 || ft_count_command(info->tokens) > 1)
		pid = fork();
	else
		pid = 0;
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		close(fd_pipe[0]);
		dup2(ft_input_fd(info->tokens, info->ordem, STDIN_FILENO), STDIN_FILENO);
        if (ft_count_command(info->tokens) > 1)
		    dup2(fd_pipe[1], STDOUT_FILENO);
		//else
		dup2(ft_output_fd(info->tokens, info->ordem, STDOUT_FILENO), STDOUT_FILENO);
		if(ft_is_builtin(flags) != 0)
			execve(path, flags, info->envp);
		else
		{
			ft_exec_builtin(flags, info, ft_count_command(info->tokens) > 1);
			dup2(ft_stdout, 1);
		}
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
		dup2(ft_input_fd(info->tokens, info->ordem, fd_pipe[0]), fd_pipe[0]);
		dup2(ft_output_fd(info->tokens, info->ordem, STDOUT_FILENO), STDOUT_FILENO);
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
	int input;
	int output;

	input = ft_input_fd(info->tokens, info->ordem, fd_pipe[0]);
	close(fd_pipe[1]);
	if (pipe(temp_fd) == -1)
		perror(strerror(errno));
	output = ft_output_fd(info->tokens, info->ordem, temp_fd[1]);
	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		close(temp_fd[0]);
		close(fd_pipe[1]);
		dup2(output, STDOUT_FILENO);
		//dup2(output, STDOUT_FILENO);
		if(ft_is_builtin(flags) != 0)
		{
			//dup2(fd_pipe[0], STDIN_FILENO);
			dup2(input, STDIN_FILENO);
			execve(path, flags, info->envp);
		}	
		else
			ft_exec_builtin(flags, info, ft_count_command(info->tokens) > 1);
	}
	waitpid(pid, &info->exit_code, 0);
	if (output == temp_fd[1])
		dup2(temp_fd[0], fd_pipe[0]);
	//else
	//	dup2(output, fd_pipe[0]);
	close(temp_fd[1]);
	close(temp_fd[0]);
}


void	ft_main_exec(t_info *info)
{
	int		pipes;
	int		fd[2];
	char	**flags;
	char	*path;
	//int 	i;

	//i = -1;
	pipes = ft_count_command(info->tokens);
	if (pipe(fd) == -1)
		perror(strerror(errno));
	while (++info->ordem < pipes) 
    {
		flags = jointokens(info->tokens, info->ordem);
		path = ft_findpath(info->tenv, flags);
        if ((path != NULL) || ft_is_builtin(flags) == 0)
		{
			if (info->ordem == 0)
				first_process(fd, flags, info, path);
			else if (info->ordem == pipes - 1)
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


