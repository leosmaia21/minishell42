/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:04:20 by bde-sous          #+#    #+#             */
/*   Updated: 2023/10/05 14:52:05 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	**ft_findpath_aux(t_envp *head)
{
	char	*p;

	p = ft_find_value(head, "PATH");
	if (!p)
		return (NULL);
	return (ft_split(p, ':'));
}

char	*ft_findpath(t_envp *head, char **flags)
{
	char	**split;
	char	*cmd_path;
	char	*aux;
	char	**aux_split;

	if (!access(flags[0], F_OK))
		return (ft_strdup(flags[0]));
	split = ft_findpath_aux(head);
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
	int	count;
	int	i;

	i = -1;
	count = 1;
	while (++i < tokens[0].total)
	{
		if (tokens[i].type == pipo)
			count++;
	}
	return (count);
}

void	ft_close_double_fd(int a, int b)
{
	close(a);
	close(b);
}

void	ft_midle_aux(int fd_pipe[2], int temp_fd[2], t_info *info)
{
	close(fd_pipe[1]);
	if (pipe(temp_fd) == -1)
		perror(strerror(errno));
	if (info->fds[0] == STDIN_FILENO)
		info->fds[0] = fd_pipe[0];
	if (info->fds[1] == STDOUT_FILENO)
		info->fds[1] = temp_fd[1];
}
