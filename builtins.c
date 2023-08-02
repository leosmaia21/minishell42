/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:36:07 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/30 22:33:58 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <assert.h>

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
	exit(1);
}

void	cd(char **info)
{
	assert(ft_strcmp(info[0], "cd") == 0);
	if (chdir(*(++info)) != 0)
		perror("cd");
	exit(1);
}

void	pwd(char **info)
{
	char	*ret;

	assert(ft_strcmp(info[0], "pwd") == 0);
	ret = getcwd(0, 0);
	if (!ret)
		perror("pwd");
	else
		printf("%s\n", ret);
	free(ret);
	exit(1);
}

void	exitsusana(char **info)
{
	assert(ft_strcmp(info[0], "exit") == 0);
	printf("Maravilha Maravilha\n");
	exit(1);
}

void	exportsusana(char **info)
{
	assert(ft_strcmp(info[0], "export") == 0);
	exit(1);
}

void	unset(char **info)
{
	assert(ft_strcmp(info[0], "unset") == 0);
	exit(1);
}

void	env(char **info, char **envp)
{
	assert(ft_strcmp(info[0], "env") == 0);
	if (envp != NULL)
    {
		while (*envp++ != NULL)
			printf("%s\n", *envp);
	}
	exit(1);
}

int ft_check_builtin(char **flags, char **envp)
{
    if (flags[0] == NULL)
        return -1;
    if (ft_strcmp(flags[0], "echo") == 0)
        echo(flags);
    else if (ft_strcmp(flags[0], "cd") == 0)
        cd(flags);
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
        return -1;
	return(0);
}