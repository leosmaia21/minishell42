/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:52:46 by bde-sous          #+#    #+#             */
/*   Updated: 2022/12/06 21:42:20 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_aux(int nb, int fd)
{
	if (nb < -9)
	{
		ft_putnbr_aux(nb / 10, fd);
		ft_putnbr_aux(nb % 10, fd);
	}
	else
	{
		ft_putchar_fd(-nb + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n >= 0)
	{
		n = -n;
		ft_putnbr_aux(n, fd);
	}
	else
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_aux(n, fd);
	}
}
