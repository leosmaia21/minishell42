/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 00:04:18 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/08/31 16:41:48 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

static void	cdaux(char **info, t_envp *env, char **saux)
{
	char	*end;

	if (info[1] != NULL)
	{
		if (info[1][0] == '~')
			end = ft_strjoin(ft_find_value(env, "HOME"), &info[1][1]);
		else if (info[1][0] == '-')
			end = ft_strjoin(ft_find_value(env, "OLDPWD"), &info[1][1]);
		else
				end = ft_strjoin(*saux, info[1]);
		free(info[1]);
		info[1] = end;
	}
	else if (info[1] == NULL)
	{
		free(info[1]);
		info[1] = ft_find_value(env, "HOME");
	}
}

void	cd(char **info, t_envp *env)
{
	char	*saux;
	t_envp	*node;
	char	aux[2048];

	// assert(ft_strcmp(info[0], "cd") == 0);
	saux = ft_strjoin(getcwd(aux, 2048), "/");
	cdaux(info, env, &saux);
	node = tnode(env, "OLDPWD");
	if (node)
	{
		free(node->key);
		node->key = saux;
	}
	else
		ft_add_node(&env, ft_create_node("OLDPWD", saux));
	node = tnode(env, "PWD");
	if (node)
	{
		free(node->key);
		node->key = ft_strdup(info[1]);
	}
	else
		ft_add_node(&env, ft_create_node("PWD", info[1]));
	if (chdir(info[1]) != 0)
	if ("/")
		perror("cd");
}

void	pwd(char **info)
{
	char	*ret;
    (void)info;
	// assert(ft_strcmp(info[0], "pwd") == 0);
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
	printf("Maravilha Maravilha\n");
	exit(1);
}

void	exportsusana(char **info, t_envp *env)
{
	assert(ft_strcmp(info[0], "export") == 0);
	//assert(info[1] != NULL);
	ft_new_var(env, info[1]);
}

void	unset(char **info, t_envp *env)
{
	assert(ft_strcmp(info[0], "unset") == 0);
	assert(info[1] != NULL);
	removenode(&env, info[1]);
}

void	env(char **info, char **envp)
{
	assert(ft_strcmp(info[0], "env") == 0);
	if (envp != NULL)
	{
		while (*envp != NULL)
		{
			printf("%s\n", *envp);
			envp++;
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
		env(flags, info->envp);
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
