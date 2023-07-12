/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:12:29 by bde-sous          #+#    #+#             */
/*   Updated: 2022/12/06 20:01:13 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	i;
	size_t	f;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	f = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) && i <= f)
		i++;
	if (i > f)
		return (ft_strdup(s1 + f + 1));
	while (ft_strchr(set, s1[f]) && f >= i)
	{
		f--;
	}
	ptr = ft_substr(s1, i, (f - i) + 1);
	return (ptr);
}
