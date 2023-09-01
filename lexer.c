/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:45:58 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/09/01 16:44:48 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"
// #include "envp.h"
// #include "libft/libft.h"
// #include "minishell.h"
// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>

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

static char	*copyuntil(char *src, char *c)
{
	long		i;
	long		x;
	char		*dst;
	long		s;

	dst = ft_calloc(ft_strlen(src) + 1, 1);
	i = -1;
	while (++i < ft_strlen(src))
	{
		x = -1;
		while (c[++x])
			if (src[i] == c[x])
				break ;
		if (src[i] == c[x])
			break ;
	}
	i = -1;
	while (++i < ft_strlen(src))
	{
		if (i == 0 && src[i] == c[x])
			dst[i] = c[x];
		if (src[i] != c[x])
			dst[i] = src[i];
		else
			break ;
	}
	return (dst);
	// s = 0;
	// i = -1;
	// while (s < ft_strlen(src))
	// {
	// 	s = (long)ft_strbrk(src + s, c) - (long)src;
	// 	if (s < 0)
	// 	{
	// 		s = ft_strlen(src);
	// 		break ;
	// 	}
	// 	if (src[s] == ' ')
	// 		break ;
	// 	s++;
	// }
	// if (s == 0)
	// 	s = 1;
	// dst = ft_calloc(s + 3, 1);
	// while (++i < s)
	// 	dst[i] = src[i];
	// return (dst);
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

static int	changetokentypesaux(t_token *tokens, int *i)
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
		if (*i < tokens[0].total - 1)
			tokens[*i + 1].type = file;
		tokens[*i].type = redirectL;
		(*i)++;
		return (1);
	}
	else if (ft_strcmp(tokens[*i].t, ">>") == 0)
	{
		if (*i < tokens[0].total - 1)
			tokens[*i + 1].type = file;
		tokens[*i].type = dredirectR;
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

static void auxremovequotes(t_token *token, char *c, int *q)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(token->t))
	{
		if (token->t[i] == '"' || token->t[i] == '\'')
		{
			*c = token->t[i];
			break ;
		}
	}
	i = -1;
	while (++i < ft_strlen(token->t))
		if (token->t[i] == *c)
			(*q)++;
}

static char	removequotes(t_token *token)
{
	int		i;
	int		n;
	int		q;
	char	*new;
	char	c;

	i = -1;
	n = 0;
	q = 0;
	c = 0;
	new = ft_calloc(ft_strlen(token->t) + 1, 1);
	auxremovequotes(token, &c, &q);
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
	return (c);
}

static void	expanddoleta(t_token *token, t_envp *env)
{
	char	*str;
	int		i;
	char 	*x;
	char	*ret;

	str = ft_calloc(ft_strlen(token->t) + 1, 1);
	i = 0;
	while (token->t[i] && token->t[i] != '$')
		i++;
	if (token->t[i] == 0)
		return ;
	i++;
	ft_strlcpy(str, token->t, i);
	ret = 0;
	while (env->next != NULL)
	{
		x =	ft_strnstr(&(token->t[i]), env->var, ft_strlen(&(token->t[i])));
		if (x)
		{
			ret = ft_strjoin(str, env->key);
			free(str);
			i += ft_strlen(env->var);
			break ;
		}
		env = env->next;
	}
	str = ft_strjoin(ret, &(token->t[i]));
	free(ret);
	free(token->t);
	token->t = str;
}

static void	dividetokensaux(t_token *tokens, int t_index, t_envp *env)
{
	int		i;
	char	c;

	i = -1;
	while (++i < t_index)
	{
		tokens[i].total = t_index;
		tokens[i].index = i;
		tokens[i].end = 0;
		c = removequotes(&tokens[i]);
		if (c != '\'' && ft_strrchr(tokens[i].t, '$'))
			expanddoleta(tokens + i, env);
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
			tokens[t_index++].t = copyquotes(&str[i], "\"");
		else if (str[i] == '\'')
			tokens[t_index++].t = copyquotes(&str[i], "\'");
		else if (str[i] != '\0')
			tokens[t_index++].t = copyuntil(&str[i], "\"\'|>< ");
		i += ft_strlen(tokens[t_index - 1].t);
	}
	dividetokensaux(tokens, t_index, env);
	return (tokens);
}
