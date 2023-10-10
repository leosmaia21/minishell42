/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:27:12 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/10 22:03:26 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

void	auxremovequotes(t_token *token, char *c, int *q)
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

void	removeaux(t_token *token, int *i, char **aux)
{
	if (token->t[i[0]] == '\'')
	{
		i[0]++;
		aux[8] = ft_calloc(ft_strlen(aux[9]) + ft_strlen(token->t) + 100, 1);
		ft_strlcpy(aux[8], aux[9], ft_strlen(aux[9]) + 1);
		free(aux[9]);
		aux[9] = aux[8];
		while (token->t[i[0]] != '\'')
		{
			aux[9][i[1]++] = token->t[i[0]++];
		}
	}
	else
	{
		aux[3] = ft_calloc(ft_strlen(aux[9]) + 100, 1);
		ft_strlcpy(aux[3], aux[9], ft_strlen(aux[9]) + 1);
		free(aux[9]);
		aux[9] = aux[3];
		if (i[1] < 0)
			i[1] = 0;
		aux[9][i[1]++] = token->t[i[0]];
	}
}

void	removea(t_token *token, t_info *info, int *i, char **aux)
{
	if (token->t[i[0]] == '$')
	{
		if (ft_strlen(token->t) == 1)
		{
			printf("$ ");
			i[0]++;
			return ;
		}
		aux[0] = expanddoleta(&(token->t[i[0]]), info, &i[0], 0);
		i[1] += ft_strlen(aux[0]);
		aux[1] = ft_strjoin(aux[9], aux[0]);
		free(aux[0]);
		free(aux[9]);
		aux[9] = aux[1];
	}
	else
		removeaux(token, i, aux);
}

void	removequotes(t_token *token, t_info *info)
{
	int		i[10];
	char	*aux[10];

	i[0] = -1;
	i[1] = 0;
	aux[9] = ft_calloc(ft_strlen(token->t) + 1, 1);
	while (++i[0] < ft_strlen(token->t) && ft_strcmp(token->t, "$"))
	{
		if (token->t[i[0]] == '"')
		{
			aux[0] = expanddoleta(&(token->t[++i[0]]), info, &i[0], 1);
			i[1] += ft_strlen(aux[0]);
			aux[1] = ft_strjoin(aux[9], aux[0]);
			free(aux[0]);
			free(aux[9]);
			aux[9] = aux[1];
		}
		else 
			removea(token, info, i, aux);
	}
	if (aux[9][0])
	{
		free(token->t);
		token->t = aux[9];
	}
}

t_token	*dividetokens(char *str, t_info *info)
{
	int			i;
	int			t_index;
	t_token		*tokens;

	tokens = ft_calloc(ft_strlen(str) + 10, sizeof(t_token));
	i = 0;
	t_index = 0;
	while (i < ft_strlen(str))
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] == '<' || str[i] == '>')
			tokens[t_index++].t = copywhileequal(&str[i], str[i]);
		else if (str[i] == '"')
			tokens[t_index++].t = copyquotes(&str[i], "\"");
		else if (str[i] == '\'')
			tokens[t_index++].t = copyquotes(&str[i], "\'");
		else if (str[i] != '\0')
			tokens[t_index++].t = copyuntil(&str[i], "|>< ");
		i += ft_strlen(tokens[t_index - 1].t);
	}
	dividetokensaux(tokens, t_index, info);
	return (tokens);
}
