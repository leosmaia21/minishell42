/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:37:11 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/10 12:52:36 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// # include "envp.h"
//# include "lexer.h"
// # include "free.h"
# include "minishell.h"

void	exitsusana(char **flags, t_info *info);
void	pwd(char **info, t_info *tinfo);
void	cd(char **info, t_envp *env, t_info *tinfo);
void	echo(char **info, t_info *tinfo);
void	exportsusana(char **info, t_envp *env, t_info *tinfo);
void	unset(char **info, t_envp *env, t_info *tinfo);
void	env(char **info, t_envp *envp, t_info *tinfo);

#endif
