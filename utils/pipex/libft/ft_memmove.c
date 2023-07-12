/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:09:12 by bde-sous          #+#    #+#             */
/*   Updated: 2022/11/12 11:58:29 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;

	if (!dst && !src)
		return (0);
	ptr = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	if (src < dst)
	{
		ptr = ptr + len - 1;
		ptr2 = ptr2 + len - 1;
		while (len--)
			*ptr-- = *ptr2--;
	}
	else
	{
		while (len--)
			*ptr++ = *ptr2++;
	}
	return (dst);
}
