/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:32:18 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/10/10 18:05:44 by ledos-sa         ###   ########.fr       */
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
	// if (info->str == NULL)
	// 	exitsusana(NULL, info);
}
