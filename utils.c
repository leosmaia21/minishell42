/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:41:20 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/09 19:41:46 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *str, int n)
{
	char	*newstr;

	newstr = malloc(n);
	ft_memset(newstr, 0, n);
	ft_strlcpy(newstr, str, ft_strlen(str) + 1);
	free(str);
	return (newstr);
}

char	*readfromstdin(void)
{
	int			n;
	char		c;
	char		*str;
	static int	size = 100;

	n = 0;
	str = malloc(size);
	ft_memset(str, 0, size);
	ft_putstr_fd("susanashell # ", 1);
	while (read(0, &c, 1) > 0)
	{
		if (n >= size)
		{
			size *= 2;
			str = ft_realloc(str, size);
		}
		if (c == '\n')
			break ;
		str[n] = c;
		n++;
	}
	return (str);
}

int	ft_get_id_pipe(t_token *tokens, int idx)
{
	int	i;

	i = -1;
	while (idx > 0)
	{
		while (tokens[++i].type != pipo)
			continue ;
		if (tokens[i].type == pipo)
			idx--;
	}
	return (i);
}

int	ft_isint(const char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (0);
	if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
	}
	if (str[i] != '\0')
		return (0);
	if (ft_atoi(str) > INT_MAX || ft_atoi(str) < INT_MIN)
		return (0);
	return (1);
}
