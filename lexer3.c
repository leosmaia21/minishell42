/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:36:16 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/30 14:37:32 by bde-sous         ###   ########.fr       */
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
	int		i;
	int 	n;
	char	*ret;
	t_envp	*cabeca;
	int q;

	str = ft_calloc(ft_strlen(token) + 1, 1);
	ret = 0;
	i = 0;
	n = 0;
	cabeca = env;
	while (token[i] && token[i] != '"')
	{
		if (token[i] != '$')
		{
			aux = ft_calloc(ft_strlen(&token[i]) + 1, 1);
			while (token[i] && token[i] != '"' && token[i] != '$')
			{
				aux[n++] = token[i++];
				*y += 1;
			}
			ret = ft_strjoin(str, aux);
			free(str);
			free(aux);
			str = ret;
			// *y += ft_findchar(&(token[i]), '"') + 1;
			if (token[i] == 0 || token[i] == '$' || token[i] == '"')
			{
				if (token[i] == '$')
					*y -= 1;
				break ;
			}
		}
		else
		{
			i++;
			while (env)
			{
				q = ft_findchar(&(token[i]), "\"$\0");
				if (d == 0)
					q = ft_findchar(&(token[i]), "$\0");
				// if (!ft_strncmp(&(token[i]), env->var, ft_findchar(&(token[i]), '"')))
				if (!ft_strncmp(&(token[i]), env->var, q))
				{
					ret = ft_strjoin(str, env->key);
					free(str);
					str = ret;
					*y += q + 1;
					i += q - 1;
					break ;
				}
				env = env->next;
			}
			env = cabeca;
			if (!ret)
			{
				q = ft_findchar(&(token[i]), "\"$\0"); 
				if (d == 0)
					q = ft_findchar(&(token[i]), "$\0");
					// q = ft_strlen(&(token[i]));
				*y += q + 1;
				i += q - 1;
			}
		}
		i++;
	}
	return (str);
}

