/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:45:58 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/17 22:00:30 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <complex.h>
#include <stdlib.h>

char	*copyuntil(char *src, char *c)
{
	long		i;
	char		*dst;
	long		s;

	s = 0;
	i = -1;
	// i = (long)ft_strbrk(src, c);
	// i = i - (long)src;
	// if (i < 0)
	// 	i = ft_strlen(src);
	// else if (i == 0)
	// 	i = 1;
	// dst = ft_calloc(i + 3, 1);
	// while (n < i && src[n])
	// {
	// 	dst[n] = src[n];
	// 	n++;
	// }
	while (s < ft_strlen(src))
	{
		s = (long)ft_strbrk(src + s, c) - (long)src;
		if (s < 0)
		{
			s = ft_strlen(src);
			break ;
		}
		if (src[s - 1] != 92)
			break ;
		s++;
	}
	if (s == 0)
		s = 1;
	dst = ft_calloc(s + 3, 1);
	while (++i < s)
		dst[i] = src[i];
	return (dst);
}

char	*copyquotes(char *src, char *c)
{
	long	i;
	long	s;
	char	*dst;

	i = -1;
	s = 0;
	while (s < ft_strlen(src))
	{
		s = (long)ft_strbrk(src + s + 1, c) - (long)src;
		if (s < 0)
		{
			s = ft_strlen(src + 1);
			break ;
		}
		if (src[s - 1] != 92)
			break ;
	}
	dst = ft_calloc(s + 3, 1);
	s++;
	while (++i < s)
		dst[i] = src[i];
	return (dst);
}

char	*copywhileequal(char *src, char c)
{
	int		i;
	char	*dst;

	i = 0;
	while (src[i] && src[i] == c)
		i++;
	dst = ft_calloc(i + 2, 1);
	i = 0;
	while (src[i] && src[i] == c)
	{
		dst[i] = src[i];
		i++;
	}
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
		else if (i > 0 && (ft_strcmp(tokens[i - 1].t, ">") == 0))
			tokens[i].type = file;
		else if (i > 0 && (ft_strcmp(tokens[i + 1].t, "<") == 0))
			tokens[i].type = file;
		else if (i > 0 && (ft_strcmp(tokens[i - 1].t, ">>") == 0))
			tokens[i].type = file;
		else if (i > 0 && (ft_strcmp(tokens[i + 1].t, "<<") == 0))
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

	tokens = ft_calloc(ft_strlen(str) + 1, sizeof(t_token));
	i = 0;
	t_index = 0;
	while (i < ft_strlen(str))
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '<' || str[i] == '>')
			tokens[t_index++].t = copywhileequal(&str[i], str[i]);
		else if (str[i] == '"')
			tokens[t_index++].t = copyquotes(&str[i], "\"");
		else if (str[i] == '\'')
			tokens[t_index++].t = copyquotes(&str[i], "\'");
		else if (str[i] != '\0')
			tokens[t_index++].t = copyuntil(&str[i], "\"\'|>< ");
		i += ft_strlen(tokens[t_index - 1].t);
	}
	i = -1;
	while (++i < t_index)
	{
		tokens[i].total = t_index;
		tokens[i].index = i;
		tokens[i].end = 0;
	}
	tokens[i].end = 1;
	tokens[i].t = "end";
	return (tokens);
}
