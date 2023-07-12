/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:28:32 by bde-sous          #+#    #+#             */
/*   Updated: 2023/03/27 18:49:32 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freedoublepointer(char **dptr)
{
	int	i;

	i = 0;
	while (dptr[i])
	{
		free(dptr[i]);
		i++;
	}
	free(dptr);
}

char	*firstword(char *str)
{
	int		i;
	char	*cmd;
	char	*rtn;

	i = 0;
	while (!ft_isalnum(*str))
		str++;
	while (ft_isalnum(str[i]) == 1 || str[i] == '/' || str[i] == '_' )
		i++;
	if (i == 0)
		return (0);
	cmd = malloc(sizeof(char) * i + 1);
	if (!cmd)
		return (0);
	ft_strlcpy(cmd, str, i + 1);
	rtn = ft_strjoin("/", cmd);
	free(cmd);
	return (rtn);
}

int	ft_checkforquotes(char *str)
{
	while (*str)
	{
		if (*str == '\'')
			return ('\'');
		if (*str == '\"')
			return ('\"');
		str++;
	}
	return (' ');
}
