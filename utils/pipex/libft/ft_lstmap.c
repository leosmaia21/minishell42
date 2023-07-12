/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:08:41 by bde-sous          #+#    #+#             */
/*   Updated: 2022/12/06 22:17:28 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_aux;
	t_list	*lst_final;

	if (!lst || !f)
		return (NULL);
	lst_final = 0;
	while (lst)
	{
		lst_aux = ft_lstnew((*f)(lst->content));
		if (!(lst_aux))
		{
			ft_lstclear(&lst_final, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_final, lst_aux);
		lst = lst->next;
	}
	return (lst_final);
}
