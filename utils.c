/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:41:20 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/14 16:43:31 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "utils.h"

char	*ft_realloc(char *str, int n)
{
	char	*newstr;

	newstr = malloc(n);
	ft_memset(newstr, 0, n);
	ft_strlcpy(newstr, str, ft_strlen(str) + 1);
	free(str);
	return (newstr);
}

char	*readfromstdin(void)
{
	int			n;
	char		c;
	char		*str;
	static int	size = 100;

	n = 0;
	str = malloc(size);
	ft_memset(str, 0, size);
	while (read(0, &c, 1) > 0)
	{
		if (n >= size)
		{
			size *= 2;
			str = ft_realloc(str, size);
		}
		if (c == '\n')
			break ;
		str[n] = c;
		n++;
	}
	return (str);
}
