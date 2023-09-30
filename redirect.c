/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:51:31 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/30 14:28:10 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

int	ft_get_id_pipe(t_token *tokens, int idx)
{
	int	i;

	i = -1;
	while (idx > 0)
	{
		while (tokens[++i].type != pipo)
			continue ;
		if (tokens[i].type == pipo)
			idx--;
	}
	return (i);
}

int	ft_process_heredoc(int i, t_info *info)
{
	int	fd;

	fd = -1;
	while ((++i < info->tokens[0].total) && (info->tokens[i].type != pipo))
	{
		if (info->tokens[i].type == dredirectL)
			fd = ft_heredoc(info->tokens[i + 1].t);
	}
	return (fd);
}

int	ft_process_input(int i, int fd_input, t_info *info, int fd_heredoc)
{
	if (fd_input != info->fds[0] && fd_input != 0)
		close(fd_input);
	if (info->tokens[i].type == dredirectL)
	{
		if (info->flag_stop != 1)
			fd_input = fd_heredoc;
	}
	else
	{
		if (info->flag_stop != 1)
		{
			if (!access(info->tokens[i + 1].t, F_OK))
				fd_input = open(info->tokens[i + 1].t, O_RDONLY);
			else
			{
				info->flag_stop = 1;
				fd_input = -1;
				perror(info->tokens[i + 1].t);
			}
		}
	}
	return (fd_input);
}

int	ft_process_output(int i, int fd, t_info *info)
{
	if (fd != info->fds[1] && fd != 1)
		close(fd);
	if (info->tokens[i].type == redirectR)
		fd = open(info->tokens[i + 1].t, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(info->tokens[i + 1].t, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
	{
		perror(info->tokens[i + 1].t);
		info->flag_stop = 1;
	}
	return (fd);
}

int	ft_process_fd(t_info *info)
{
	int	fd_input;
	int	fd_output;
	int	i;
	int	erro;
	int	fd_heredoc;

	erro = 1;
	i = ft_get_id_pipe(info->tokens, info->ordem);
	fd_input = info->fds[0];
	fd_output = info->fds[1];
	fd_heredoc = ft_process_heredoc(i, info);
	while ((++i < info->tokens[0].total) && (info->tokens[i].type != pipo) && erro)
	{
		if ((info->tokens[i].type == redirectL) || (info->tokens[i].type == dredirectL))
		{
			info->fds[0] = ft_process_input(i, fd_input, info, fd_heredoc);
			i++;
		}
		if ((info->tokens[i].type == redirectR) || (info->tokens[i].type == dredirectR))
		{
			info->fds[1] = ft_process_output(i, fd_output, info);
			if (info->tokens[i + 2].type == pipo)
				return (erro);
			i++;
		}
		if ((info->fds[0] == -1) || (info->fds[1] == -1))
			erro = 0;
	}
	return (erro);
}
