/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 10:53:47 by bde-sous          #+#    #+#             */
/*   Updated: 2022/11/05 10:53:47 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;

	if ((!(dst) || !(src)) && dstsize == 0)
		return (0);
	if (dstsize < ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	j = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= j)
		return (ft_strlen(src) + dstsize);
	i = 0;
	while (i < dstsize - j - 1 && src[i] != '\0')
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
