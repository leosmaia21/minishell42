/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:07:24 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/30 16:10:37 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

int	ft_heredoc(char *escape);
int	ft_process_input(int i, int fd_input, t_info *info, int fd_heredoc);
int	ft_process_output(int i, int fd, t_info *info);
int	ft_process_fd(t_info *info);

#endif