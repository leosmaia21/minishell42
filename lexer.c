/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 lexer.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: bde-sous <bde-sous@student.42porto.com>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2023/07/14 16:45:58 by ledos-sa		   #+#	  #+#			  */
/*	 Updated: 2023/09/13 14:19:36 by ledos-sa		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"
#include "utils/pipex/libft/libft.h"

char	**jointokens(t_token *tokens, int idx)
{
	int		i;
	char	*str[2];
	char	**ret;

	i = -1;
	while (idx > 0)
	{
		while (tokens[++i].type != pipo)
			continue ;
		if (tokens[i].type == pipo)
			idx--;
	}
	while (tokens[++i].type != command)
	{
		if((tokens[i].type == pipo) || (i == tokens[0].total))
			return(NULL);
	}
	str[0] = ft_strdup(tokens[i].t);
	i++;
	while ((tokens[i].type != pipo) && (i < tokens[0].total))
	{
		if (tokens[i].type == flag)
		{	
			str[1] = ft_strjoin(str[0], "]");
			free(str[0]);
			str[0] = ft_strjoin(str[1], tokens[i].t);
			free(str[1]);
		}
		i++;
	}
	ret = ft_split(str[0], ']');
	free(str[0]);
	return (ret);
}

char	*copyuntil(char *src, char *c)
{
	long		i[2];
	char		*dst;

	dst = ft_calloc(ft_strlen(src) + 1, 1);
	i[0] = -1;
	while (++i[0] < ft_strlen(src))
	{
		i[1] = -1;
		while (c[++i[1]])
			if (src[i[0]] == c[i[1]])
				break ;
		if (src[i[0]] == c[i[1]])
			break ;
	}
	i[0] = -1;
	while (++i[0] < ft_strlen(src))
	{
		if (i[0] == 0 && src[i[0]] == c[i[1]])
			dst[i[0]] = c[i[1]];
		if (src[i[0]] != c[i[1]])
			dst[i[0]] = src[i[0]];
		else
			break ;
	}
	return (dst);
}

char	*copyquotes(char *src, char *c)
{
	long	i;
	long	s;
	char	*dst;

	i = -1;
	s = 0;
	while (s < ft_strlen(src))
	{
		s = (long)ft_strbrk(src + s + 1, c) - (long)src;
		if (s < 0)
		{
			s = ft_strlen(src + 1);
			break ;
		}
		if (src[s + 1] == ' ')
			break ;
	}
	dst = ft_calloc(s + 3, 1);
	s++;
	while (++i < s)
		dst[i] = src[i];
	return (dst);
}

char	*copywhileequal(char *src, char c)
{
	int		i;
	char	*dst;

	i = 0;
	while (src[i] && src[i] == c)
		i++;
	dst = ft_calloc(i + 2, 1);
	i = 0;
	while (src[i] && src[i] == c)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

int	changetokentypesaux(t_token *tokens, int *i)
{
	if (ft_strcmp(tokens[*i].t, ">") == 0)
	{
		if (*i < tokens[0].total - 1)
			tokens[*i + 1].type = file;
		tokens[*i].type = redirectR;
		(*i)++;
		return (1);
	}
	else if (ft_strcmp(tokens[*i].t, "<") == 0)
	{
		if (*i < tokens[0].total - 1)
			tokens[*i + 1].type = file;
		tokens[*i].type = redirectL;
		(*i)++;
		return (1);
	}
	else if (ft_strcmp(tokens[*i].t, ">>") == 0)
	{
		if (*i < tokens[0].total - 1)
			tokens[*i + 1].type = file;
		tokens[*i].type = dredirectR;
		(*i)++;
		return (1);
	}
	return (0);
}

void	changetokentypes(t_token *tokens)
{
	int		i;

	i = -1;
	while (++i < tokens[0].total)
	{
		if (ft_strcmp(tokens[i].t, "|") == 0)
			tokens[i].type = pipo;
		else if (changetokentypesaux(tokens, &i))
			continue ;
		else if (ft_strcmp(tokens[i].t, "<<") == 0)
		{
			if (i < tokens[0].total - 1)
				tokens[i + 1].type = file;
			tokens[i].type = dredirectL;
			i++;
		}
		else if (tokens[i].t[0] == '-' || (i > 0 && (tokens[i - 1].type == flag \
			|| tokens[i - 1].type == command)))
			tokens[i].type = flag;
		else if (tokens[i].t[0] == '"')
			tokens[i].type = text;
		else
			tokens[i].type = command;
	}
}


void	expandoletafree(t_token *token, char *ret, int i, char *str)
{
	str = ft_strjoin(ret, &(token->t[i]));
	if (!str)
		str = ft_calloc(1, 1);
	free(ret);
	free(token->t);
	token->t = str;
}

int	ft_findchar(char *str, char *c)
{
	int	i;
	int	k;

	i = -1;
	while (++i <= ft_strlen(str))
	{
		k = -1;
		while (++k <= ft_strlen(c))
			if (str[i] == c[k])
				return (i);
	}
	return (0);
}

char	*expanddoleta(char *token, t_envp *env, int *y, int d)
{
	char	*str;
	char	*aux;
	int		i;
	int 	n;
	char	*ret;
	t_envp	*cabeca;
	int q;

	str = ft_calloc(ft_strlen(token) + 1, 1);
	ret = 0;
	i = 0;
	n = 0;
	cabeca = env;
	while (token[i] && token[i] != '"')
	{
		if (token[i] != '$')
		{
			aux = ft_calloc(ft_strlen(&token[i]) + 1, 1);
			while (token[i] && token[i] != '"' && token[i] != '$')
			{
				aux[n++] = token[i++];
				*y += 1;
			}
			ret = ft_strjoin(str, aux);
			free(str);
			free(aux);
			str = ret;
			// *y += ft_findchar(&(token[i]), '"') + 1;
			if (token[i] == 0 || token[i] == '$' || token[i] == '"')
			{
				if (token[i] == '$')
					*y -= 1;
				break ;
			}
		}
		else
		{
			i++;
			while (env)
			{
				q = ft_findchar(&(token[i]), "\"$\0");
				if (d == 0)
					q = ft_findchar(&(token[i]), "$\0");
				// if (!ft_strncmp(&(token[i]), env->var, ft_findchar(&(token[i]), '"')))
				if (!ft_strncmp(&(token[i]), env->var, q))
				{
					ret = ft_strjoin(str, env->key);
					free(str);
					str = ret;
					*y += q + 1;
					i += q - 1;
					break ;
				}
				env = env->next;
			}
			env = cabeca;
			if (!ret)
			{
				q = ft_findchar(&(token[i]), "\"$\0"); 
				if (d == 0)
					q = ft_findchar(&(token[i]), "$\0");
					// q = ft_strlen(&(token[i]));
				*y += q + 1;
				i += q - 1;
			}
		}
		i++;
	}
	return (str);
}

void	auxremovequotes(t_token *token, char *c, int *q)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(token->t))
	{
		if (token->t[i] == '"' || token->t[i] == '\'')
		{
			*c = token->t[i];
			break ;
		}
	}
	i = -1;
	while (++i < ft_strlen(token->t))
		if (token->t[i] == *c)
			(*q)++;
}

char	removequotes(t_token *token, t_envp *env)
{
	int		i;
	int		n;
	char	*new;
	char	*aux[10];

	i = -1;
	n = 0;
	new = ft_calloc(ft_strlen(token->t) + 1, 1);
	// auxremovequotes(token, &c, &q);
	i = -1;
	while (++i < ft_strlen(token->t))
	{
		if (token->t[i] == '"')
		{
			i++;
			aux[0] = expanddoleta(&(token->t[i]), env, &i, 1);
			n += ft_strlen(aux[0]);
			aux[1] = ft_strjoin(new, aux[0]);
			free(aux[0]);
			free(new);
			new = aux[1];
		}
		else if(token->t[i] == '$')
		{
			aux[0] = expanddoleta(&(token->t[i]), env, &i, 0);
			n += ft_strlen(aux[0]) - 1;
			aux[1] = ft_strjoin(new, aux[0]);
			free(aux[0]);
			free(new);
			new = aux[1];
		}
		else if (token->t[i] == '\'')
		{
			i++;
			while (token->t[i] != '\'')
				new[n++] = token->t[i++];
		}
		else
		{
			aux[3] = ft_calloc(ft_strlen(new) + 100, 1);
			ft_strlcpy(aux[3], new, ft_strlen(new) + 1);
			free(new);
			new = aux[3];
			if (n < 0)
				n = 0;
			new[n++] = token->t[i];
		}
	}
	free(token->t);
	token->t = new;
	return (0);
}

void	dividetokensaux(t_token *tokens, int t_index, t_envp *env)
{
	int		i;

	i = -1;
	while (++i < t_index)
	{
		tokens[i].total = t_index;
		tokens[i].index = i;
		tokens[i].end = 0;
		removequotes(&tokens[i], env);
	}
	tokens[i].end = 1;
	tokens[i].t = "end";
}

t_token	*dividetokens(char *str, t_envp *env)
{
	int			i;
	int			t_index;
	t_token		*tokens;

	tokens = ft_calloc(ft_strlen(str) + 10, sizeof(t_token));
	i = 0;
	t_index = 0;
	while (i < ft_strlen(str))
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '\0')
			return(NULL);
		if (str[i] == '<' || str[i] == '>')
			tokens[t_index++].t = copywhileequal(&str[i], str[i]);
		else if (str[i] == '"')
			tokens[t_index++].t = copyquotes(&str[i], "\"");
		else if (str[i] == '\'')
			tokens[t_index++].t = copyquotes(&str[i], "\'");
		else if (str[i] != '\0')
			tokens[t_index++].t = copyuntil(&str[i], "|>< ");
		i += ft_strlen(tokens[t_index - 1].t);
	}
	dividetokensaux(tokens, t_index, env);
	return (tokens);
}
