/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:36:07 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/08/03 18:50:32 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"
#include <assert.h>
#include <stdlib.h>

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

void	cd(char **info, t_envp *env)
{
	char	*saux;
	char	*end;
	t_envp	*node;
	char	aux[2048];

	assert(ft_strcmp(info[0], "cd") == 0);
	saux = ft_strjoin(getcwd(aux, 2048), "/");
	if (info[1] != NULL)
	{
		if (info[1][0] == '~')
			end = ft_strjoin(ft_find_value(env, "HOME"), &info[1][1]);
		else if (info[1][0] == '-')
			end = ft_strjoin(ft_find_value(env, "OLDPWD"), &info[1][1]);
		else
			end = ft_strjoin(saux, info[1]);
		free(info[1]);
		info[1] = end;
	}
	else if (info[1] == NULL)
	{
		free(info[1]);
		info[1] = ft_find_value(env, "HOME");
	}
	node = tnode(env, "OLDPWD");
	free(node->key);
	node->key = saux;
	node = tnode(env, "PWD");
	free(node->key);
	node->key = info[1];
	if (chdir(info[1]) != 0)
		perror("cd");
}

void	pwd(char **info)
{
	char	*ret;

	// assert(ft_strcmp(info[0], "pwd") == 0);
	ret = getcwd(0, 0);
	if (!ret)
		perror("pwd");
	else
		printf("%s\n", ret);
	free(ret);
}

void	exitsusana(char **info)
{
	assert(ft_strcmp(info[0], "exit") == 0);
	printf("Maravilha Maravilha\n");
	//exit(1);
}

void	exportsusana(char **info)
{
	assert(ft_strcmp(info[0], "export") == 0);
	//exit(1);
}

void	unset(char **info)
{
	assert(ft_strcmp(info[0], "unset") == 0);
	//exit(1);
}

void	env(char **info, char **envp)
{
	assert(ft_strcmp(info[0], "env") == 0);
	if (envp != NULL)
    {
		while (*envp++ != NULL)
			printf("%s\n", *envp);
	}
	//exit(1);
}

int ft_check_builtin(char **flags, char **envp, t_envp *e)
{
    if (flags[0] == NULL)
        return -1;
    if (ft_strcmp(flags[0], "echo") == 0)
        echo(flags);
    else if (ft_strcmp(flags[0], "cd") == 0)
        cd(flags, e);
    else if (ft_strcmp(flags[0], "pwd") == 0)
        pwd(flags);
    else if (ft_strcmp(flags[0], "export") == 0)
        exportsusana(flags);
    else if (ft_strcmp(flags[0], "unset") == 0)
        unset(flags);
    else if (ft_strcmp(flags[0], "env") == 0)
        env(flags, envp);
    else if (ft_strcmp(flags[0], "exit") == 0)
        exitsusana(flags);
		else
			return(-1);
	return(0);
}

