/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:20:14 by bde-sous          #+#    #+#             */
/*   Updated: 2022/12/06 21:42:48 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!(s))
		return (0);
	i = ft_strlen(s);
	if (i < start)
	{
		str = malloc(sizeof(char) * 1);
		if (!(str))
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!(str))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
		if (i++ >= start && j < len)
			str[j++] = s[i - 1];
	str[j] = '\0';
	return (str);
}
