/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:37:11 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/08/03 18:09:23 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "envp.h"
# include "lexer.h"
# include "libft/libft.h"
# include "minishell.h"
# include <unistd.h>

void	exitsusana(char **info);
void	pwd(char **info);
void	cd(char **info, t_envp *env);
void	echo(char **info);
void	exportsusana(char **info);
void	unset(char **info);
void	env(char **info, char **envp);

#endif
