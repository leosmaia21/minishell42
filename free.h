/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:58 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/08/10 22:19:32 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H
# include "minishell.h"

void	ft_freestr(void *dptr);
void 	ft_freestruct(t_info *info);
void 	ft_freelistenv(t_envp *lst);
void	ft_freedoublepointer(char **dptr);
void    ft_freetokens(t_token *tokens);

#endif
