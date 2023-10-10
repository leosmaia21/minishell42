/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:58 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/10 11:48:35 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_exp
{
	char	*str;
	char	*aux;
	char	*ret;
	int		i[10];
	t_envp	*cabeca;
	int		*y;
	int		d;
}	t_exp;

t_token	*dividetokens(char *str, t_info *info);
char	**jointokens(t_token *tokens, int idx);
void	changetokentypes(t_token *tokens);
char	*copyuntil(char *src, char *c);
char	*copyquotes(char *src, char *c);
char	*copywhileequal(char *src, char c);
int		changetokentypesaux(t_token *tokens, int *i);
void	changetokentypes(t_token *tokens);
void	auxremovequotes(t_token *token, char *c, int *q);
char	removequotes(t_token *token, t_info *info);
void	expandoletafree(t_token *token, char *ret, int i, char *str);;
char	*expanddoleta(char *token, t_info *info, int *y, int d);
void	dividetokensaux(t_token *tokens, int t_index, t_info *info);
t_token	*dividetokens(char *str, t_info *info);
int		ft_findchar(char *str, char *c);
void	jointokens_aux(int i, t_token *tokens, char **str);
void	dividetokensaux(t_token *tokens, int t_index, t_info *info);

#endif
