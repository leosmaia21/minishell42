/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 00:33:37 by bde-sous          #+#    #+#             */
/*   Updated: 2022/11/08 00:52:10 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	pos;
	int	atoi;

	atoi = 0;
	pos = 1;
	while (*str == ' ' || ((*str >= '\t') && (*str <= '\r')))
		str++;
	if (*str == '-')
	{	
		pos = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{	
		atoi = atoi * 10 + (str[0] - '0');
		str++;
	}
	return (atoi * pos);
}
