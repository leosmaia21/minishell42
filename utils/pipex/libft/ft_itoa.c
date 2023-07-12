/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:02:10 by bde-sous          #+#    #+#             */
/*   Updated: 2022/11/16 18:51:46 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_ilen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		ilen;
	char	*itoa;

	ilen = ft_ilen(n);
	itoa = malloc(sizeof(char) * (ilen + 1));
	if (!itoa)
		return (0);
	itoa[ilen--] = '\0';
	if (n == 0)
		itoa[0] = '0';
	if (n >= 0)
		n *= -1;
	else
		itoa[0] = '-';
	while (n < 0)
	{
		itoa[ilen--] = 48 + ((n % -10) * -1);
		n = ((n / -10) * -1);
	}
	return (itoa);
}
