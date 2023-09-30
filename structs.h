/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:03:01 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/30 16:11:41 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

typedef struct s_envp{
	char			*var;
	char			*key;
	int				equal;
	struct s_envp	*next;
}	t_envp;

typedef struct s_token{
	char			*t;
	t_tokentype		type;
	int				total;
	int				index;
	int				end;
	int				pipe;
	int				expandenv;
}	t_token;

typedef struct s_info{
	char			*str;
	t_envp			*tenv;
	char			**envp;
	t_token			*tokens;
	int				exit_code;
	int				ordem;
	int				fds[2];
	int				flag_stop;
}	t_info;

#endif