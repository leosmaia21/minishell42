/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:58 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/22 17:15:43 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_token_type{
	command,
	flag,
	redirectL,
	dredirectL,
	redirectR,
	dredirectR,
	pipo,
	text,
	file
}	t_tokentype;

typedef struct s_token{
	char			*t;
	t_tokentype		type;
	int				total;
	int				index;
	int				end;
	int				pipe;
}	t_token;

t_token	*dividetokens(char *str);
char	**jointokens(t_token *tokens);
void	changetokentypes(t_token *tokens);
#endif
