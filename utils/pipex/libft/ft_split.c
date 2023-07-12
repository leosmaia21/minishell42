/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:15:50 by bde-sous          #+#    #+#             */
/*   Updated: 2022/11/19 14:04:38 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countchr(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static void	ft_free(char **spl, int j)
{
	while (j-- > 0)
		free(spl[j]);
	free(spl);
}

static int	ft_calclen(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	char			**spl;
	int				i;
	unsigned int	j;

	i = 0;
	j = -1;
	if (!s)
		return (0);
	spl = (char **)malloc((ft_countchr(s, c) + 1) * sizeof(char *));
	if (!(spl))
		return (0);
	while (++j < ft_countchr(s, c))
	{
		while (s[i] == c)
			i++;
		spl[j] = ft_substr(s, i, ft_calclen(s, c, i));
		if (!(spl))
		{
			ft_free(spl, j);
			return (0);
		}
		i += ft_calclen(s, c, i);
	}
	spl[j] = 0;
	return (spl);
}
