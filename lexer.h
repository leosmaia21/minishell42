/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:58 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/09/30 14:52:18 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

t_token	*dividetokens(char *str, t_envp *env);
char	**jointokens(t_token *tokens, int idx);
void	changetokentypes(t_token *tokens);
char	*copyuntil(char *src, char *c);
char	*copyquotes(char *src, char *c);
char	*copywhileequal(char *src, char c);
int		changetokentypesaux(t_token *tokens, int *i);
void	changetokentypes(t_token *tokens);
void	auxremovequotes(t_token *token, char *c, int *q);
char	removequotes(t_token *token, t_envp *env);
void	expandoletafree(t_token *token, char *ret, int i, char *str);;
char	*expanddoleta(char *token, t_envp *env, int *y, int d);
void	dividetokensaux(t_token *tokens, int t_index, t_envp *env);
t_token	*dividetokens(char *str, t_envp *env);

#endif
