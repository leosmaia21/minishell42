/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:36:18 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/30 14:50:20 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

char	**jointokens(t_token *tokens, int idx)
{
	int		i;
	char	*str[2];
	char	**ret;

	i = -1;
	while (idx > 0)
	{
		while (tokens[++i].type != pipo)
			continue ;
		if (tokens[i].type == pipo)
			idx--;
	}
	while (tokens[++i].type != command)
	{
		if ((tokens[i].type == pipo) || (i == tokens[0].total))
			return (NULL);
	}
	str[0] = ft_strdup(tokens[i].t);
	i++;
	while ((tokens[i].type != pipo) && (i < tokens[0].total))
	{
		if (tokens[i].type == flag)
		{
			str[1] = ft_strjoin(str[0], "]");
			free(str[0]);
			str[0] = ft_strjoin(str[1], tokens[i].t);
			free(str[1]);
		}
		i++;
	}
	ret = ft_split(str[0], ']');
	free(str[0]);
	return (ret);
}

char	*copyuntil(char *src, char *c)
{
	long		i[2];
	char		*dst;

	dst = ft_calloc(ft_strlen(src) + 1, 1);
	i[0] = -1;
	while (++i[0] < ft_strlen(src))
	{
		i[1] = -1;
		while (c[++i[1]])
			if (src[i[0]] == c[i[1]])
				break ;
		if (src[i[0]] == c[i[1]])
			break ;
	}
	i[0] = -1;
	while (++i[0] < ft_strlen(src))
	{
		if (i[0] == 0 && src[i[0]] == c[i[1]])
			dst[i[0]] = c[i[1]];
		if (src[i[0]] != c[i[1]])
			dst[i[0]] = src[i[0]];
		else
			break ;
	}
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
		if (src[s + 1] == ' ')
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

int	changetokentypesaux(t_token *tokens, int *i)
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
