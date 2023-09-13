/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:04:23 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/09/12 15:44:21 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	ft_freestr(void *dptr)
{
	if (dptr)
		free(dptr);
}

void	ft_freedoublepointer(char **dptr)
{
	int	i;

	i = -1;
	while (dptr[++i] != NULL)
		ft_freestr(dptr[i]);
	ft_freestr(dptr);
}

void	ft_freelistenv(t_envp *lst)
{
	t_envp	*head;

	head = lst;
	while (lst)
	{
		head = lst->next;
		ft_freestr(lst->var);
		ft_freestr(lst->key);
		ft_freestr(lst);
		lst = head;
	}
}

void	ft_freetokens(t_token *tokens)
{
	int	i;
	int	total;

	total = tokens->total;
	i = -1;
	if (tokens == NULL)
		return ;
	while (++i < total)
	{
		ft_freestr(tokens[i].t);
	}
	ft_freestr(tokens);
}

void	ft_freestruct(t_info *info)
{
	ft_freestr(info->str);
	ft_freelistenv(info->tenv);
	ft_freedoublepointer(info->envp);
	ft_freetokens(info->tokens);
}
