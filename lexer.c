/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:34:31 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/30 14:49:26 by bde-sous         ###   ########.fr       */
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

char	removequotes(t_token *token, t_envp *env)
{
	int		i;
	int		n;
	char	*new;
	char	*aux[10];

	i = -1;
	n = 0;
	new = ft_calloc(ft_strlen(token->t) + 1, 1);
	i = -1;
	while (++i < ft_strlen(token->t))
	{
		if (token->t[i] == '"')
		{
			i++;
			aux[0] = expanddoleta(&(token->t[i]), env, &i, 1);
			n += ft_strlen(aux[0]);
			aux[1] = ft_strjoin(new, aux[0]);
			free(aux[0]);
			free(new);
			new = aux[1];
		}
		else if (token->t[i] == '$')
		{
			aux[0] = expanddoleta(&(token->t[i]), env, &i, 0);
			n += ft_strlen(aux[0]) - 1;
			aux[1] = ft_strjoin(new, aux[0]);
			free(aux[0]);
			free(new);
			new = aux[1];
		}
		else if (token->t[i] == '\'')
		{
			i++;
			while (token->t[i] != '\'')
				new[n++] = token->t[i++];
		}
		else
		{
			aux[3] = ft_calloc(ft_strlen(new) + 100, 1);
			ft_strlcpy(aux[3], new, ft_strlen(new) + 1);
			free(new);
			new = aux[3];
			if (n < 0)
				n = 0;
			new[n++] = token->t[i];
		}
	}
	free(token->t);
	token->t = new;
	return (0);
}

void	dividetokensaux(t_token *tokens, int t_index, t_envp *env)
{
	int		i;

	i = -1;
	while (++i < t_index)
	{
		tokens[i].total = t_index;
		tokens[i].index = i;
		tokens[i].end = 0;
		removequotes(&tokens[i], env);
	}
	tokens[i].end = 1;
	tokens[i].t = "end";
}

t_token	*dividetokens(char *str, t_envp *env)
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
			return (NULL);
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
	dividetokensaux(tokens, t_index, env);
	return (tokens);
}
