/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:55:12 by bde-sous          #+#    #+#             */
/*   Updated: 2023/10/12 21:20:54 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECS_H
# define EXECS_H

# include "minishell.h"

int		ft_envlstsize(t_envp *lst);
int		ft_count_command(t_token *tokens);
void	ft_close_double_fd(int a, int b);
void	ft_midle_aux(int fd_pipe[2], int temp_fd[2], t_info *info);
int		first_process_aux(char **flags, t_info *info, int fd_pipe[2]);
void	ft_execve(char **flags, t_info *info);
#endif
