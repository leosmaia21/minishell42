/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:32:18 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/11 19:23:39 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

void	funcao(t_info *info)
{
	info->tokens = NULL;
	info->envp = list_to_doublepointer(info->tenv);
	signals();
	info->str = readline("\033[1;95msusanashell # \033[0m");
	if (info->str == NULL)
		exitsusana(NULL, info);
}
