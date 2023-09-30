/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:36:16 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/30 22:23:31 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"

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

void	expandoletafree(t_token *token, char *ret, int i, char *str)
{
	str = ft_strjoin(ret, &(token->t[i]));
	if (!str)
		str = ft_calloc(1, 1);
	free(ret);
	free(token->t);
	token->t = str;
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

char	*expanddoleta(char *token, t_envp *env, int *y, int d)
{
	char	*str;
	char	*aux;
	int		i[10];
	char	*ret;
	t_envp	*cabeca;

	str = ft_calloc(ft_strlen(token) + 1, 1);
	ret = 0;
	i[0] = 0;
	i[2] = 0;
	cabeca = env;
	while (token[i[0]] && token[i[0]] != '"')
	{
		if (token[i[0]] == '\'')
		{
			(*y)--;
			break ;
		}
		if (token[i[0]] != '$')
		{
			aux = ft_calloc(ft_strlen(&token[i[0]]) + 1, 1);
			while (token[i[0]] && token[i[0]] != '"' && token[i[0]] != '$')
			{
				aux[i[2]++] = token[i[0]++];
				*y += 1;
			}
			ret = ft_strjoin(str, aux);
			free(str);
			free(aux);
			str = ret;
			if (token[i[0]] == 0 || token[i[0]] == '$')
			{
				if (token[i[0]] == '$')
					*y -= 1;
				break ;
			}
		}
		else
		{
			i[0]++;
			while (env)
			{
				i[1] = ft_findchar(&(token[i[0]]), "\"$\0'");
				if (d == 0)
					i[1] = ft_findchar(&(token[i[0]]), "\"'$\0'");
				if (!ft_strncmp(&(token[i[0]]), env->var, i[1]))
				{
					ret = ft_strjoin(str, env->key);
					free(str);
					str = ret;
					*y += i[1] + 1;
					i[0] += i[1] - 1;
					break ;
				}
				env = env->next;
			}
			env = cabeca;
			if (!ret)
			{
				i[1] = ft_findchar(&(token[i[0]]), "\"$\0"); 
				if (d == 0)
					i[1] = ft_findchar(&(token[i[0]]), "'$\0");
				*y += i[1] + 1;
				i[0] += i[1] - 1;
			}
		}
		i[0]++;
	}
	return (str);
}
