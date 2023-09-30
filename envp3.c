/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 12:46:08 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/30 14:02:35 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

t_envp	*ft_new_var(t_envp *head, char *str)
{
	t_envp	*node;
	char	*var;
	char	*key;

	var = ft_substr(str, 0, ft_strchr(str, '=') - str);
	key = ft_substr(str, (ft_strchr(str, '=') - str) + 1, ft_strlen(str));
	if (ft_change_var(head, key, var, str))
		return (head);
	node = ft_create_node(var, key);
	node->equal = 1;
	if (!ft_strchr(str, '='))
		node->equal = 0;
	if (!node) 
	{
		free(var);
		free(key);
	}
	else
		ft_add_node(&head, node);
	return (head);
}

t_envp	*ft_convert_envp(char **envp)
{
	t_envp	*head; 
	t_envp	*node; 
	char	*var;
	char	*key;
	int		i;

	head = NULL;
	i = -1;
	while (envp[++i] != NULL) 
	{
		if (ft_strchr(envp[i], '='))
		{
			var = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
			key = ft_substr(envp[i], (ft_strchr(envp[i], '=') - envp[i]) + 1, \
				ft_strlen(envp[i]));
			node = ft_create_node(var, key);
			if (!node) 
			{
				free(var);
				free(key);
				while (head != NULL) 
				{
					node = head;
					head = head->next;
					free(node->var);
					free(node->key);
					free(node);
				}
				return (0);
			}
			ft_add_node(&head, node);
		}
	}
	return (head);
}
