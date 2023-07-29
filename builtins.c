/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:36:07 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/29 15:40:03 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	echoval(char *info)
{
	int		i;
	char	*s;
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
	if (chdir(*(++info)) != 0)
		perror("chdir() error()");
}

void	pwd(char **info)
{
	char	*ret;

	ret = getcwd(0, 0);
	if (!ret)
		perror("getcwd() error");
	else
		printf("%s\n", ret);
	free(ret);
}

void	exitsusana(void)
{
	printf("Maravilha Maravilha\n");
	exit(1);
}
