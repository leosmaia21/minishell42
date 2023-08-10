/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:37:11 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/08/10 21:14:48 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// # include "envp.h"
//# include "lexer.h"
// # include "free.h"
# include "minishell.h"

void	exitsusana(char **flags, t_info *info);
void	pwd(char **info);
void	cd(char **info, t_envp *env);
void	echo(char **info);
void	exportsusana(char **info, t_envp *env);
void	unset(char **info, t_envp *env);
void	env(char **info, char **envp);

#endif
