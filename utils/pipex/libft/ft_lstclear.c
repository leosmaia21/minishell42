/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:40:00 by bde-sous          #+#    #+#             */
/*   Updated: 2022/12/06 22:08:13 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst1;
	t_list	*lst_aux;

	if (!lst || !del)
		return ;
	lst1 = *lst;
	while (lst1)
	{
		lst_aux = lst1->next;
		ft_lstdelone(lst1, del);
		lst1 = lst_aux;
	}
	*lst = NULL;
}
