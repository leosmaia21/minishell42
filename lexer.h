/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:58 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/08/10 21:25:57 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

t_token	*dividetokens(char *str, t_envp *env);
char	**jointokens(t_token *tokens, int idx);
void	changetokentypes(t_token *tokens);
#endif
