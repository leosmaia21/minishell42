/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:24:24 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/12 21:31:40 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execs.h"
#include "lexer.h"

void	first_process(int fd_pipe[2], char **flags, t_info *info)
{
	int		pid;
	int		fd_stdout;

	fd_stdout = dup(1);
	pid = first_process_aux(flags, info, fd_pipe);
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		close(fd_pipe[0]);
		dup2(info->fds[1], STDOUT_FILENO);
		if (ft_is_builtin(flags) != 0)
		{
			dup2(info->fds[0], STDIN_FILENO);
			ft_execve(flags, info);
		}
		else
			ft_exec_builtin(flags, info, ft_count_command(info->tokens) > 1);
	}
	if (info->fds[1] != STDOUT_FILENO || ft_count_command(info->tokens) > 1)
	{
		if (info->fds[1] != fd_pipe[1])
			close(info->fds[1]);
	}
	dup2(fd_stdout, 1);
}

void	second_process(int fd_pipe[2], char **flags, t_info *info)
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
			ft_execve(flags, info);
		}
		else
			ft_exec_builtin(flags, info, 1);
	}
	ft_close_double_fd(fd_pipe[0], fd_pipe[1]);
	if (info->fds[1] != STDOUT_FILENO)
		close(info->fds[1]);
}

void	midle_process(int fd_pipe[2], char **flags, t_info *info)
{
	int	pid;
	int	temp_fd[2];

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
			ft_execve(flags, info);
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
	if (ft_process_fd(info))
	{
		if (info->ordem == 0)
			first_process(fd, flags, info);
		else if (info->ordem == pipes - 1)
			second_process(fd, flags, info);
		else
			midle_process(fd, flags, info);
	}
	signal(SIGINT, SIG_IGN);
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
		info->fds[0] = 0;
		info->fds[1] = 1;
		ft_freedoublepointer(flags);
	}
	while (waitpid(0, &info->exit_code, 0) > 0)
		continue ;
}
