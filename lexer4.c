/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:43:16 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/10 11:48:19 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"
#include <assert.h>

void	changetokentypes(t_token *tokens)
{
	int		i;

	i = -1;
	while (++i < tokens[0].total)
	{
		if (ft_strcmp(tokens[i].t, "|") == 0)
			tokens[i].type = pipo;
		else if (changetokentypesaux(tokens, &i))
			continue ;
		else if (ft_strcmp(tokens[i].t, "<<") == 0)
		{
			if (i < tokens[0].total - 1)
				tokens[i + 1].type = file;
			tokens[i].type = dredirectL;
			i++;
		}
		else if (tokens[i].t[0] == '-' || (i > 0 && (tokens[i - 1].type == flag \
			|| tokens[i - 1].type == command)))
			tokens[i].type = flag;
		else if (tokens[i].t[0] == '"')
			tokens[i].type = text;
		else
			tokens[i].type = command;
	}
}

int	ft_findchar(char *str, char *c)
{
	int	i;
	int	k;

	i = -1;
	while (++i <= ft_strlen(str))
	{
		k = -1;
		while (++k <= ft_strlen(c))
			if (str[i] == c[k])
				return (i);
	}
	return (0);
}

void	jointokens_aux(int i, t_token *tokens, char **str)
{
	while ((tokens[i].type != pipo) && (i < tokens[0].total))
	{
		if (tokens[i].type == flag)
		{
			str[1] = ft_strjoin(str[0], str[2]);
			free(str[0]);
			str[0] = ft_strjoin(str[1], tokens[i].t);
			free(str[1]);
		}
		i++;
	}
}

char	**jointokens(t_token *tokens, int idx)
{
	int		i;
	char	*str[2];
	char	**ret;

	i = -1;
	while (idx >= 0)
	{
		while (tokens[++i].type != command)
			continue ;
		if (tokens[i].type == command)
			idx--;
	}
	str[0] = ft_strdup(tokens[i].t);
	i++;
	while (tokens[i].type == flag)
	{
		str[1] = ft_strjoin(str[0], "]");
		free(str[0]);
		str[0] = ft_strjoin(str[1], tokens[i].t);
		free(str[1]);
		i++;
	}
	ret = ft_split(str[0], ']');
	free(str[0]);
	return (ret);
}

void	dividetokensaux(t_token *tokens, int t_index, t_info *info)
{
	int		i;

	i = -1;
	while (++i < t_index)
	{
		tokens[i].total = t_index;
		tokens[i].index = i;
		tokens[i].end = 0;
		removequotes(&tokens[i], info);
	}
	tokens[i].end = 1;
	tokens[i].t = "end";
}
