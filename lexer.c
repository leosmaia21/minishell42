/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:45:58 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/08/03 17:48:06 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char	**jointokens(t_token *tokens, int idx)
{
	int		i;
	char	*str;

	i = -1;
	str = "";
	while (idx >= 0)
	{
		while (tokens[++i].type != command)
			continue ;
		if (tokens[i].type == command)
			idx--;
	}
	str = ft_strjoin(str, tokens[i].t);
	i++;
	while (tokens[i].type == flag)
	{
		str = ft_strjoin(str, " ");
		str = ft_strjoin(str, tokens[i].t);
		i++;
	}
	return (ft_split(str, ' '));
}

static char	*copyuntil(char *src, char *c)
{
	long		i;
	char		*dst;
	long		s;

	s = 0;
	i = -1;
	while (s < ft_strlen(src))
	{
		s = (long)ft_strbrk(src + s, c) - (long)src;
		if (s < 0)
		{
			s = ft_strlen(src);
			break ;
		}
		if (src[s] == ' ')
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

static char	*copyquotes(char *src, char *c)
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
		if (src[s + 1] == ' ')
			break ;
	}
	dst = ft_calloc(s + 3, 1);
	s++;
	while (++i < s)
		dst[i] = src[i];
	return (dst);
}

static char	*copywhileequal(char *src, char c)
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

static int	changetokentypes2(t_token *tokens, int *i)
{
	if (ft_strcmp(tokens[*i].t, ">") == 0)
	{
		if (*i < tokens[0].total - 1)
			tokens[*i + 1].type = file;
		tokens[*i].type = redirectR;
		(*i)++;
		return (1);
	}
	else if (ft_strcmp(tokens[*i].t, "<") == 0)
	{
		if (*i > 0)
			tokens[*i - 1].type = file;
		tokens[*i].type = redirectL;
		return (1);
	}
	else if (ft_strcmp(tokens[*i].t, ">>") == 0)
	{
		if (*i < tokens[0].total - 1)
			tokens[*i + 1].type = file;
		tokens[*i].type = dredirectL;
		(*i)++;
		return (1);
	}
	return (0);
}

void	changetokentypes(t_token *tokens)
{
	int		i;

	i = -1;
	while (++i < tokens[0].total)
	{
		if (ft_strcmp(tokens[i].t, "|") == 0)
			tokens[i].type = pipo;
		else if (changetokentypes2(tokens, &i))
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

static void	removequotes(t_token *token)
{
	int		i;
	int		n;
	int		q;
	char	*new;
	char	c;

	i = -1;
	n = 0;
	q = 0;
	new = ft_calloc(ft_strlen(token->t) + 1, 1);
	while (++i < ft_strlen(token->t))
	{
		if (token->t[i] == '"' || token->t[i] == '\'')
		{
			c = token->t[i];
			break ;
		}
	}
	i = -1;
	while (++i < ft_strlen(token->t))
		if (token->t[i] == c)
			q++;
	i = -1;
	while (++i < ft_strlen(token->t)) 
	{
			if (token->t[i] != c)
			new[n++] = token->t[i];
	}
	if (q % 2)
		new[n] = c;
	free(token->t);
	token->t = new;
	if (c == '\'')
		token->squote = 1;
	else
		token->squote = 0;
}

static void	dividetokensaux(t_token *tokens, int t_index)
{
	int	i;

	i = -1;
	while (++i < t_index)
	{
		tokens[i].total = t_index;
		tokens[i].index = i;
		tokens[i].end = 0;
		removequotes(&tokens[i]);
	}
	tokens[i].end = 1;
	tokens[i].t = "end";
}

t_token	*dividetokens(char *str, t_envp *env)
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
			tokens[t_index++].t = (copyquotes(&str[i], "\""));
		else if (str[i] == '\'')
			tokens[t_index++].t = (copyquotes(&str[i], "\'"));
		else if (str[i] != '\0')
			tokens[t_index++].t = copyuntil(&str[i], "\"\'|>< ");
		i += ft_strlen(tokens[t_index - 1].t);
	}
	dividetokensaux(tokens, t_index);
	return (tokens);
}
