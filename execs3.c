/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:24:24 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/10 12:29:20 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execs.h"
#include "lexer.h"

int	first_process_aux(char **flags, t_info *info, int fd_pipe[2])
{
	int	pid;

	if (ft_is_builtin(flags) != 0 || ft_count_command(info->tokens) > 1)
		pid = fork();
	else
		pid = 0;
	if (ft_count_command(info->tokens) > 1 && info->fds[1] == STDOUT_FILENO)
		info->fds[1] = fd_pipe[1];
	return (pid);
}

void	ft_execve(char *path, char **flags, t_info *info)
{
	if (execve(path, flags, info->envp) == -1)
		perror(flags[0]);
	exit(1);
}
