/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:58 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/14 18:30:17 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_token_type{
	command,
	flag,
	redirect
}	t_token_type;

typedef struct s_token{
	char			*t;
	t_token_type	type;
	int				total;
	int				index;
}	t_token;

t_token	*dividetokens(char *str);
#endif
