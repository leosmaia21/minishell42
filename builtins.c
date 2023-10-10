/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 00:04:18 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/10 12:46:30 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"
#include "minishell.h"
#include "structs.h"
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

void	echo(char **info, t_info *tinfo)
{
	int		i[100];

	ft_memset(i, 0, sizeof(i));
	while (info[++i[0]])
	{
		i[1] = echoval(info[i[0]]);
		if (i[1] == 1)
			i[2] = 1;
		else
			break ;
	}
	while (info[i[0]])
	{
		printf("%s", info[i[0]]);
		if (info[i[0] + 1])
			printf(" ");
		i[0]++;
	}
	if (i[2] == 0)
		printf("\n");
	tinfo->exit_code = 0;
}

void	pwd(char **info, t_info *tinfo)
{
	char	*ret;

	(void)info;
	assert(ft_strcmp(info[0], "pwd") == 0);
	ret = getcwd(0, 0);
	if (!ret)
	{
		perror("pwd");
		tinfo->exit_code = 1;
	}
	else
	{
		printf("%s\n", ret);
		tinfo->exit_code = 0;
	}
	free(ret);
}

void	exportsusana(char **info, t_envp *env, t_info *tinfo)
{
	if (info[1] != 0 && ft_isdigit(info[1][0]) == 1)
	{
		printf("export: `%s': not a valid identifier\n", info[1]);
		tinfo->exit_code = 1;
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
	tinfo->exit_code = 0;
}

void	unset(char **info, t_envp *env, t_info *tinfo)
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
	tinfo->exit_code = 0;
}
