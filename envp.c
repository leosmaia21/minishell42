
#include "envp.h"
#include "minishell.h"

t_envp *ft_create_node(char *var, char *key)
{
	t_envp *node = (t_envp *)malloc(sizeof(t_envp));
	if (!node) 
		return(0);
	node->var = ft_strdup(var);
	node->key = ft_strdup(key);
	node->next = NULL;
	return (node);
}

void ft_add_node(t_envp **head, t_envp *node)
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

t_envp *ft_new_var(t_envp *head, char *str)
{
	t_envp	*node;
	char	*var;
	char	*key;

	if (ft_strchr(str, '='))
	{
		var = ft_substr(str, 0, ft_strchr(str, '=') - str);
		key = ft_substr(str, (ft_strchr(str, '=') - str)+ 1, ft_strlen(str));
		node = ft_create_node(var, key);
		if (!node) 
		{
			free(var);
			free(key);
		}
		else
			ft_add_node(&head, node);
	}
	else
		printf("failed to create node");
	return(head);
}

t_envp *ft_convert_envp(char **envp)
{
	t_envp	*head; 
	t_envp	*node; 
	char	*var;
	char	*key;
	int		i;

	head = NULL;
	i = -1;
	while(envp[++i] != NULL) 
	{
		if (ft_strchr(envp[i], '='))
		{
			var = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
			key = ft_substr(envp[i], (ft_strchr(envp[i], '=') - envp[i])+ 1, ft_strlen(envp[i]));
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
				return(0);
			}
			ft_add_node(&head, node);
		}
	}
	return(head);
}

t_envp	*tnode(t_envp *cabeca, char *key)
{
	while(cabeca != NULL)
	{
		if (!ft_strcmp(cabeca->var, key))
			break;
		cabeca = cabeca->next;
	}
	return(cabeca);
}

void printEnvpList(t_envp *head) 
{
	t_envp *current = head;

	while (current != NULL) 
	{
		printf("declare -x %s=%s\n", current->var, current->key);
		current = current->next;
	}
}

char *ft_find_value(t_envp *head, char *key)
{
	while(head != NULL)
	{
		if (!ft_strcmp(head->var, key))
			break;
		head = head->next;
	}
	return(head->key);
}


char **ft_duplicate_envp(char **envp) 
{
	int envpCount;
	char **duplicatedEnvp;
	int i;

	envpCount = 0;
	i = -1;
	if (envp == NULL)
		return (NULL);
	while (envp[envpCount] != NULL) 
		envpCount++;
	duplicatedEnvp = (char **)malloc(sizeof(char *) * (envpCount + 1));
	if (duplicatedEnvp == NULL) 
		return (NULL);
	while (++i < envpCount) 
	{
		duplicatedEnvp[i] = ft_strdup(envp[i]);
		if (duplicatedEnvp[i] == NULL) 
		{
			ft_freedoublepointer(duplicatedEnvp);
			return (NULL);
		}
	}
	duplicatedEnvp[envpCount] = NULL;
	return(duplicatedEnvp);
}
