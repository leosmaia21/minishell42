/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:10:45 by bde-sous          #+#    #+#             */
/*   Updated: 2022/11/19 13:55:31 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((!(haystack) || !(needle)) && len == 0)
		return (0);
	if (!needle[i])
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] && i + j < len)
			j++;
		if (!needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}

// int main()
// {
//     char palehiro[50] = "Rei do Bacalhau comeu Batatinhas";
//     char agulha [20] = "R";
//     char *ptr;
//     char *ft_ptr;
//     ptr=strnstr(palehiro,agulha,50);
//     ft_ptr=ft_strnstr(palehiro,agulha,50);
//     return(0);
// }