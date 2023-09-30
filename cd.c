/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 12:30:35 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/30 12:42:08 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"
#include "minishell.h"
#include <string.h>
#include <unistd.h>

static char	*cdaux(char **info, t_envp *env, char *saux)
{
	char	*end;
	char	*ret;

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
