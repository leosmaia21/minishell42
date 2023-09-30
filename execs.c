/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:24:24 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/09/30 14:17:55 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execs.h"
#include "lexer.h"

void	first_process(int fd_pipe[2], char **flags, t_info *info, char *path)
{
	int		pid;
	int		fd_stdout;

	fd_stdout = dup(1);
	if (ft_is_builtin(flags) != 0 || ft_count_command(info->tokens) > 1)
		pid = fork();
	else
		pid = 0;
	if (ft_count_command(info->tokens) > 1 && info->fds[1] == STDOUT_FILENO)
		info->fds[1] = fd_pipe[1];
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		close(fd_pipe[0]);
		dup2(info->fds[1], STDOUT_FILENO);
		if (ft_is_builtin(flags) != 0)
		{
			dup2(info->fds[0], STDIN_FILENO);
			execve(path, flags, info->envp);
		}
		else
			ft_exec_builtin(flags, info, ft_count_command(info->tokens) > 1);
	}
	if (info->fds[1] != STDOUT_FILENO || ft_count_command(info->tokens) > 1)
		close(info->fds[1]);
	dup2(fd_stdout, 1);
}

void	second_process(int fd_pipe[2], char **flags, t_info *info, char *path)
{
	int		pid;

	if (info->fds[0] == STDIN_FILENO)
		info->fds[0] = fd_pipe[0];
	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		dup2(info->fds[0], fd_pipe[0]);
		dup2(info->fds[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		if (ft_is_builtin(flags) != 0)
		{
			dup2(fd_pipe[0], STDIN_FILENO);
			execve(path, flags, info->envp);
		}
		else
			ft_exec_builtin(flags, info, 1);
	}
	close(fd_pipe[0]);
	if (info->fds[1] != STDOUT_FILENO)
		close(info->fds[1]);
}

void	midle_process(int fd_pipe[2], char **flags, t_info *info, char *path)
{
	int	pid;
	int	temp_fd[2];

	close(fd_pipe[1]);
	if (pipe(temp_fd) == -1)
		perror(strerror(errno));
	ft_midle_aux(fd_pipe, temp_fd, info);
	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		ft_close_double_fd(temp_fd[0], fd_pipe[1]);
		dup2(info->fds[1], STDOUT_FILENO);
		if (ft_is_builtin(flags) != 0)
		{
			dup2(info->fds[0], STDIN_FILENO);
			execve(path, flags, info->envp);
		}
		else
			ft_exec_builtin(flags, info, ft_count_command(info->tokens) > 1);
	}
	if (info->fds[1] == temp_fd[1])
		dup2(temp_fd[0], fd_pipe[0]);
	ft_close_double_fd(temp_fd[0], temp_fd[1]);
}

void	ft_exec_loop(t_info *info, char **flags, int *fd, int pipes)
{
	char	*path;

	path = ft_findpath(info->tenv, flags);
	if ((path != NULL) || ft_is_builtin(flags) == 0)
	{
		if (ft_process_fd(info))
		{
			if (info->ordem == 0)
				first_process(fd, flags, info, path);
			else if (info->ordem == pipes - 1)
				second_process(fd, flags, info, path);
			else
				midle_process(fd, flags, info, path);
		}
	}
	else
	{
		ft_process_fd(info);
		if (ft_strcmp(flags[0], "end") != 0)
			perror(flags[0]);
	}
	ft_freestr(path);
	ft_freedoublepointer(flags);
}

void	ft_main_exec(t_info *info)
{
	int		pipes;
	int		fd[2];
	char	**flags;

	pipes = ft_count_command(info->tokens);
	if (pipe(fd) == -1)
		perror(strerror(errno));
	while (++info->ordem < pipes)
	{
		flags = jointokens(info->tokens, info->ordem);
		if (flags)
			ft_exec_loop(info, flags, fd, pipes);
		else
			ft_process_fd(info);
		info->flag_stop = 0;
		info->fds[0] = 0;
		info->fds[1] = 1;
	}
	while (waitpid(0, &info->exit_code, 0) > 0)
		continue ;
}
