/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 00:04:18 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/09/30 15:48:58 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"
#include "minishell.h"
#include <string.h>
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

void	exportsusana(char **info, t_envp *env)
{
	if (info[1] != 0 && ft_isdigit(info[1][0]) == 1)
	{
		printf("export: `%s': not a valid identifier\n", info[1]);
		return ;
	}
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
	int		i;

	i = 0;
	assert(ft_strcmp(info[0], "unset") == 0);
	if (info[1])
	{
		while (info[++i])
		{
			removenode(&env, info[i]);
		}
	}
}
