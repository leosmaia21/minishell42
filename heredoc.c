/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:26:48 by bde-sous          #+#    #+#             */
/*   Updated: 2023/10/09 20:04:52 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

int	ft_heredoc_aux(char *str, char *escape, int fd[2])
{
	str = readline("> ");
	if (ft_strcmp(str, escape) == 0) 
	{
		free(str);
		return (0);
	}
	ft_putstr_fd(str, fd[1]);
	ft_putstr_fd("\n", fd[1]);
	free(str);
	return (1);
}

int	ft_heredoc_aux2(char *str, char *escape, int fd[2], int pid)
{
	int		fd_return;

	if (pid == 0) 
	{
		close(fd[0]);
		while (ft_heredoc_aux(str, escape, fd)) 
			;
		close(fd[1]);
		exit(0); 
	}
	else 
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		fd_return = dup(fd[0]);
		close(fd[0]);
	}
	return (fd_return);
}

int	ft_heredoc(char *escape)
{
	int		fd[2];
	int		pid;
	char	*str;

	str = NULL;
	if (pipe(fd) == -1) 
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1) 
	{
		perror("fork");
		return (-1);
	}
	return (ft_heredoc_aux2(str, escape, fd, pid));
}
