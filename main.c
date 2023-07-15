/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:53:46 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/14 19:30:27 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "utils.h"
#include <stdio.h>
#include "lexer.h"

int	main(void)
{
	char *str = readfromstdin();
	t_token *tokens = dividetokens(str);
	for (int i = 0; i < tokens[0].total; i++) {
		printf("%s\n", tokens[i].t);
	}

}
