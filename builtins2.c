/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 00:04:18 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/09/30 12:37:43 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"
#include "minishell.h"
#include <string.h>
#include <unistd.h>

void	exitsusana(char **flags, t_info *info)
{
	assert(ft_strcmp(flags[0], "exit") == 0);
	ft_freestruct(info);
	rl_clear_history();
	printf("exit\n");
	exit(info->exit_code);
}

void	env(char **info, t_envp *envp)
{
	assert(ft_strcmp(info[0], "env") == 0);
	if (envp != NULL)
	{
		while (envp)
		{
			if (ft_strlen(envp->key))
				printf("%s=%s\n", envp->var, envp->key);
			else if (envp->equal == 1)
				printf("%s=\n", envp->var);
			envp = envp->next;
		}
	}
}

void	ft_exec_builtin(char **flags, t_info *info, int exit_flag)
{
	if (ft_strcmp(flags[0], "echo") == 0)
		echo(flags);
	else if (ft_strcmp(flags[0], "cd") == 0)
		cd(flags, info->tenv);
	else if (ft_strcmp(flags[0], "pwd") == 0)
		pwd(flags);
	else if (ft_strcmp(flags[0], "export") == 0)
		exportsusana(flags, info->tenv);
	else if (ft_strcmp(flags[0], "unset") == 0)
		unset(flags, info->tenv);
	else if (ft_strcmp(flags[0], "env") == 0)
		env(flags, info->tenv);
	else if (ft_strcmp(flags[0], "exit") == 0)
		exitsusana(flags, info);
	if (exit_flag)
		exit(0);
}

int	ft_is_builtin(char **flags)
{
	if (flags[0] == NULL)
		return (-1);
	if (ft_strcmp(flags[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(flags[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(flags[0], "pwd") == 0)
		return (0);
	else if (ft_strcmp(flags[0], "export") == 0)
		return (0);
	else if (ft_strcmp(flags[0], "unset") == 0)
		return (0);
	else if (ft_strcmp(flags[0], "env") == 0)
		return (0);
	else if (ft_strcmp(flags[0], "exit") == 0)
		return (0);
	else
		return (-1);
	return (0);
}
