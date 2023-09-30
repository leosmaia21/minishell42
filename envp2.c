/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 12:44:21 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/30 12:55:04 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

t_envp	*ft_create_node(char *var, char *key)
{
	t_envp	*node;

	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node) 
		return (0);
	node->var = ft_strdup(var);
	node->key = ft_strdup(key);
	node->next = NULL;
	if (var)
		ft_freestr(var);
	if (key)
		ft_freestr(key);
	return (node);
}

void	ft_add_node(t_envp **head, t_envp *node)
{
	t_envp	*temp;

	if (!(*head)) 
		*head = node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}

int	ft_change_var(t_envp *head, char *key, char *var, char *str)
{
	while (head != NULL)
	{
		if (!ft_strcmp(head->var, var))
		{
			free(head->key);
			head->key = ft_strdup(key);
			free(var);
			free(key);
			head->equal = 1;
			if (!ft_strchr(str, '='))
				head->equal = 0;
			return (1);
		}
		head = head->next;
	}
	return (0);
}

void	printenvplist(t_envp *head)
{
	t_envp	*current;

	current = head;
	while (current != NULL) 
	{
		printf("declare -x %s=%s\n", current->var, current->key);
		current = current->next;
	}
}

int	ft_envlstsize(t_envp *lst)
{
	int		x;

	x = 0;
	while (lst)
	{
		lst = lst->next;
		x++;
	}
	return (x);
}
