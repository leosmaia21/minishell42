/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:27:00 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/09 19:43:32 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft/libft.h"
#include "minishell.h"

void	removenode(t_envp **head, char *key)
{
	t_envp	*temp;
	t_envp	*current;

	current = *head;
	temp = *head;
	while (*head && !ft_strcmp((*head)->var, key))
	{
		*head = (*head)->next;
		free(temp);
	}
	if (!*head) 
		return ;
	while (current->next) 
	{
		if (!ft_strcmp(current->next->var, key))
		{
			temp = current->next;
			current->next = temp->next;
			free(temp);
		}
		else 
			current = current->next;
	}
}

t_envp	*tnode(t_envp *cabeca, char *key)
{
	while (cabeca != NULL)
	{
		if (!ft_strcmp(cabeca->var, key))
			break ;
		cabeca = cabeca->next;
	}
	return (cabeca);
}

char	*ft_find_value(t_envp *head, char *key)
{
	while (head != NULL)
	{
		if (!ft_strcmp(head->var, key))
			break ;
		head = head->next;
	}
	if (!head)
		return (NULL);
	return (head->key);
}

char	**ft_duplicate_envp(char **envp)
{
	int		envpcount;
	char	**duplicatedenvp;
	int		i;

	envpcount = 0;
	i = -1;
	if (envp == NULL)
		return (NULL);
	while (envp[envpcount] != NULL) 
		envpcount++;
	duplicatedenvp = (char **)malloc(sizeof(char *) * (envpcount + 1));
	if (duplicatedenvp == NULL) 
		return (NULL);
	while (++i < envpcount) 
	{
		duplicatedenvp[i] = ft_strdup(envp[i]);
		if (duplicatedenvp[i] == NULL) 
		{
			ft_freedoublepointer(duplicatedenvp);
			return (NULL);
		}
	}
	duplicatedenvp[envpcount] = NULL;
	return (duplicatedenvp);
}

char	**list_to_doublepointer(t_envp *head)
{
	t_envp	*c;
	char	**envp;
	int		i;
	char	*tmp;

	i = 0;
	envp = (char **)ft_calloc(sizeof(char *), (ft_envlstsize(head) + 1));
	if (!envp)
		return (NULL);
	c = head;
	while (c != NULL)
	{
		envp[i] = (char *)malloc(ft_strlen(c->var) + ft_strlen(c->key) + 2);
		if (!envp[i])
		{
			ft_freedoublepointer(envp);
			return (NULL);
		}
		tmp = ft_strjoin(c->var, "=");
		free(envp[i]);
		envp[i++] = ft_strjoin(tmp, c->key);
		free(tmp);
		c = c->next;
	}
	return (envp);
}
