/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:25:23 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/10 12:25:27 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"
#include "minishell.h"
#include <string.h>
#include <unistd.h>

void	free_and_exit(char **flags, t_info *info, int exit_code)
{
	ft_freestruct(info);
	ft_freedoublepointer(flags);
	rl_clear_history();
	exit(exit_code);
}

void	exitsusana(char **flags, t_info *info)
{
	printf("exit\n");
	if (!flags)
		free_and_exit(flags, info, info->exit_code);
	if (!flags[1])
		free_and_exit(flags, info, info->exit_code);
	if (!ft_isint(flags[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(flags[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		free_and_exit(flags, info, 2);
	}
	if (ft_isint(flags[1]) && flags[2] == NULL)
		exit((unsigned char)ft_atoi(flags[1]));
	printf("minishell: exit: too many arguments\n");
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
