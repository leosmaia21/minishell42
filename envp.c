/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:27:00 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/09/11 20:55:41 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "minishell.h"

t_envp	*ft_create_node(char *var, char *key)
{
	t_envp *node;

	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node) 
		return (0);
	node->var = ft_strdup(var);
	node->key = ft_strdup(key);
	node->next = NULL;
	ft_freestr(var);
	ft_freestr(key);
	return (node);
}

void	ft_add_node(t_envp **head, t_envp *node)
{
	t_envp *temp;

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

int	ft_change_var(t_envp *head, char *key, char *var)
{
	while (head != NULL)
	{
		if (!ft_strcmp(head->var, var))
		{
			free(head->key);
			head->key = ft_strdup(key);
			free(var);
			free(key);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

t_envp	*ft_new_var(t_envp *head, char *str)
{
	t_envp	*node;
	char	*var;
	char	*key;

	var = ft_substr(str, 0, ft_strchr(str, '=') - str);
	key = ft_substr(str, (ft_strchr(str, '=') - str) + 1, ft_strlen(str));
	if (ft_change_var(head, key, var))
		return (head);
	node = ft_create_node(var, key);
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
			key = ft_substr(envp[i], (ft_strchr(envp[i], '=') - envp[i]) + 1, ft_strlen(envp[i]));
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

void	printEnvpList(t_envp *head)
{
	t_envp *current;

	current = head;
	while (current != NULL) 
	{
		printf("declare -x %s=%s\n", current->var, current->key);
		current = current->next;
	}
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
		return(NULL);
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

char	**list_to_doublepointer(t_envp *head)
{
	t_envp	*current;
	char 	**envp;
	int 	i;
	char 	*tmp;

	i = 0;
	envp = (char **)ft_calloc(sizeof(char *), (ft_envlstsize(head) + 1));
	if (!envp)
		return NULL;
	current = head;
	while (current != NULL)
	{
		envp[i] = (char *)malloc(ft_strlen(current->var) + ft_strlen(current->key) + 2);
		if (!envp[i])
		{
			ft_freedoublepointer(envp);
			return NULL;
		}
		tmp = ft_strjoin(current->var, "=");
		free(envp[i]);
		envp[i] = ft_strjoin(tmp, current->key);
		i++;
		free(tmp);
		current = current->next;
	}
	return (envp);
}


