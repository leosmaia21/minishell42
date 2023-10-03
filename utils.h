/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:42:23 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/03 21:08:11 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

char	*ft_realloc(char *str, int n);
char	*readfromstdin(void);
int		ft_get_id_pipe(t_token *tokens, int idx);
int     ft_isint(const char *str);

#endif
