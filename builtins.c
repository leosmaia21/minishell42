/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:36:07 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/29 16:46:33 by ledos-sa         ###   ########.fr       */
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
			{
				n = 1;
			}
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

void	cd(char **info)
{
	assert(ft_strcmp(info[0], "cd") == 0);
	if (chdir(*(++info)) != 0)
		perror("cd");
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
}

void	exitsusana(char **info)
{
	assert(ft_strcmp(info[0], "exit") == 0);
	printf("Maravilha Maravilha\n");
	exit(1);
}
