/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 00:04:18 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/09/16 18:36:15 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>

static int	echoval(char *info)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (info[0] == '-')
	{
		while (info[++i])
		{
			if (info[i] == 'n')
				n = 1;
			else
			{
				n = 0;
				break ;
			}
		}
	}
	return (n);
}

void	echo(char **info)
{
	int		x;
	int		i;
	int		n;

	i = 0;
	x = 0;
	n = 0;
	assert(ft_strcmp(info[0], "echo") == 0);
	while (info[++i])
	{
		x = echoval(info[i]);
		if (x == 1)
			n = 1;
		else
			break ;
	}
	while (info[i])
	{
		printf("%s", info[i]);
		if (info[i + 1])
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
}

static char	*cdaux(char **info, t_envp *env, char *saux)
{
	char	*end;
	char 	*ret;

	if (info[1] != NULL)
	{
		if (info[1][0] == '~')
			end = ft_strjoin(ft_find_value(env, "HOME"), &info[1][1]);
		else if (info[1][0] == '-')
			end = ft_strjoin(ft_find_value(env, "OLDPWD"), &info[1][1]);
		else if (info[1][0] == '/')
			end = ft_strdup(info[1]);
		else
			end = ft_strjoin(saux, info[1]);
		ret = end;
	}
	else
	{
		ret = ft_strdup(ft_find_value(env, "HOME"));
	}
	free(saux);
	return (ret);
}

void	cd(char **info, t_envp *env)
{
	char	*saux;
	t_envp	*node;
	char	*path;
	char	aux[2048];

	saux = ft_strjoin(getcwd(aux, 2048), "/");
	path = cdaux(info, env, saux);
	node = tnode(env, "OLDPWD");
	if (node)
	{
		free(node->key);
		node->key = getcwd(0, 0);
	}
	else
		ft_add_node(&env, ft_create_node(ft_strdup("OLDPWD"), getcwd(0, 0)));
	node = tnode(env, "PWD");
	if (chdir(path) != 0)
		perror("cd");
	free(path);
	if (node)
	{
		free(node->key);
		node->key = getcwd(0, 0);
	}
	else
		ft_add_node(&env, ft_create_node("PWD", getcwd(0, 0)));
}

void	pwd(char **info)
{
	char	*ret;

	(void)info;
	assert(ft_strcmp(info[0], "pwd") == 0);
	ret = getcwd(0, 0);
	if (!ret)
		perror("pwd");
	else
		printf("%s\n", ret);
	free(ret);
}

void	exitsusana(char **flags, t_info *info)
{
	assert(ft_strcmp(flags[0], "exit") == 0);
	ft_freestruct(info);
	rl_clear_history();
	printf("exit\n");
	exit(info->exit_code);
}

void	exportsusana(char **info, t_envp *env)
{
	if (info[1])
		ft_new_var(env, info[1]);
	else
	{
		while (env)
		{
			if (ft_strlen(env->key))
				printf("declare -x %s=%s\n", env->var, env->key);
			else if (env->equal == 0)
				printf("declare -x %s\n", env->var);
			else if (env->equal == 1)
				printf("declare -x %s=\"\"\n", env->var);
			env = env->next;
		}
	}
}

void	unset(char **info, t_envp *env)
{
	int	i;

	i = 0;
	assert(ft_strcmp(info[0], "unset") == 0);
	if (info[1])
		while (info[++i])
			removenode(&env, info[1]);
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
			else if (envp->equal == 0)
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
