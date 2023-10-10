/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:29:28 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/10 15:33:29 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"
#include <assert.h>

int	expaux1(t_exp *exp, char *token)
{
	exp->aux = ft_calloc(ft_strlen(&token[exp->i[0]]) + 1, 1);
	while (token[exp->i[0]] && token[exp->i[0]] != '"' && \
		token[exp->i[0]] != '$')
	{
		exp->aux[exp->i[2]++] = token[exp->i[0]++];
		*exp->y += 1;
	}
	exp->ret = ft_strjoin(exp->str, exp->aux);
	free(exp->str);
	free(exp->aux);
	exp->str = exp->ret;
	if (token[exp->i[0]] == 0 || token[exp->i[0]] == '$')
	{
		if (token[exp->i[0]] == '$')
			*exp->y -= 1;
		return (1);
	}
	return (0);
}

void	initexpandoleta(t_exp *exp, char *token, t_info *info, int *y)
{
	char	*aux;
	char	*aux2;

	exp->str = ft_calloc(ft_strlen(token) + 1, 1);
	exp->ret = 0;
	ft_memset(exp->i, 0, sizeof(int) * 10);
	exp->cabeca = info->tenv;
	exp->y = y;
	aux = ft_itoa(info->exit_code);
	aux2 = ft_strjoin("?=", aux);
	ft_new_var(info->tenv, aux2);
	free(aux);
	free(aux2);
}

void	expaux3(t_exp *exp, t_info *info)
{
	exp->ret = ft_strjoin(exp->str, info->tenv->key);
	free(exp->str);
	exp->str = exp->ret;
	*exp->y += exp->i[1] + 1;
	exp->i[0] += exp->i[1] - 1;
}

void	expaux2(t_exp *exp, char *token, t_info *info)
{
	exp->i[0]++;
	exp->ret = 0;
	while (info->tenv)
	{
		exp->i[1] = ft_findchar(&(token[exp->i[0]]), "'/\"\0/");
		if (exp->d == 0)
			exp->i[1] = ft_findchar(&(token[exp->i[0]]), "\"/'$\0'");
		if (!ft_strncmp(&(token[exp->i[0]]), info->tenv->var, exp->i[1]))
		{
			expaux3(exp, info);
			break ;
		}
		info->tenv = info->tenv->next;
	}
	info->tenv = exp->cabeca;
	if (!exp->ret)
	{
		exp->i[1] = ft_findchar(&(token[exp->i[0]]), "'/\"\0/");
		if (exp->d == 0)
			exp->i[1] = ft_findchar(&(token[exp->i[0]]), "\"/'$\0'");
		*exp->y += exp->i[1] + 1;
		exp->i[0] += exp->i[1] - 1;
	}
}

char	*expanddoleta(char *token, t_info *info, int *y, int d)
{
	t_exp	exp;	

	initexpandoleta(&exp, token, info, y);
	exp.d = d;
	while (token[exp.i[0]] && token[exp.i[0]] != '"')
	{
		if (token[exp.i[0]] == '\'')
		{
			(*exp.y)--;
			break ;
		}
		if (token[exp.i[0]] != '$')
		{
			if (expaux1(&exp, token))
				break ;
		}
		else
			expaux2(&exp, token, info);
		exp.i[0]++;
	}
	removenode(&(info->tenv), "?");
	return (exp.str);
}
