/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:47:24 by bde-sous          #+#    #+#             */
/*   Updated: 2022/12/06 21:45:33 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_aux;

	if (!lst || !f)
		return ;
	lst_aux = lst;
	while (lst_aux)
	{
		f(lst_aux->content);
		lst_aux = lst_aux->next;
	}
}
