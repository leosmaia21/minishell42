/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:45:58 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/14 20:06:44 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"
#include "utils.h"

char	*copyuntil(char *src, char c)
{
	int		i;
	char	*dst;

	i = 1;
	while (src[i] != c && src[i])
		i++;
	dst = ft_calloc(i + 2, 1);
	i = 0;
	if (c == '"')
		i++;
	while (src[i] != c && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (c == '"')
	{
		dst[0] = c;
		dst[i] = 0;
		if (src[i] == c)
			dst[i] = c;
	}
	else
		dst[i] = 0;
	return (dst);
}

void	changetokentypes(t_token *tokens)
{
	int		i;

	i = -1;
	if (!tokens)
		return ;
	while (++i < tokens[0].total)
	{
		if (ft_strcmp(tokens[i].t, "|") == 0)
			tokens[i].type = pipo;
		else if (tokens[i].t[0] == '-')
			tokens[i].type = flag;
		else if (tokens[i].t[0] == '"')
			tokens[i].type = text;
		else if (ft_strcmp(tokens[i].t, ">>") == 0)
			tokens[i].type = dredirectR;
		else if (ft_strcmp(tokens[i].t, "<<") == 0)
			tokens[i].type = dredirectL;
		else if (ft_strcmp(tokens[i].t, ">") == 0)
			tokens[i].type = redirectR;
		else if (ft_strcmp(tokens[i].t, "<") == 0)
			tokens[i].type = redirectL;
		else if (i > 0 && (ft_strcmp(tokens[i - 1].t, "<") == 0))
			tokens[i].type = file;
		else if (i > 0 && (ft_strcmp(tokens[i + 1].t, ">") == 0))
			tokens[i].type = file;
		else if (i > 0 && (ft_strcmp(tokens[i - 1].t, "<<") == 0))
			tokens[i].type = file;
		else if (i > 0 && (ft_strcmp(tokens[i + 1].t, ">>") == 0))
			tokens[i].type = file;
		else
			tokens[i].type = command;
	}
}

t_token	*dividetokens(char *str)
{
	int			i;
	int			t_index;
	t_token		*tokens;

	tokens = ft_calloc(ft_strlen(str), sizeof(t_token));
	i = 0;
	t_index = 0;
	while (i < ft_strlen(str))
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '"')
			tokens[t_index++].t = copyuntil(&str[i], '"');
		else 
			tokens[t_index++].t = copyuntil(&str[i], ' ');
		i += ft_strlen(tokens[t_index - 1].t);
	}
	i = -1;
	while (++i < t_index)
	{
		tokens[i].total = t_index;
		tokens[i].index = i;
	}
	return (tokens);
}
