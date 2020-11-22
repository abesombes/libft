/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesombe <abesombe@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 22:35:27 by abesombe          #+#    #+#             */
/*   Updated: 2020/11/22 12:35:27 by abesombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	nwords(char const *s1, char c)
{
	int		count;
	int		nword;

	count = 0;
	nword = 0;
	if (*s1 == '\0')
		return (0);
	while (*s1)
	{
		if (*s1 == c)
			nword = 0;
		else if (nword == 0)
		{
			nword = 1;
			count++;
		}
		s1++;
	}
	return (count);
}

static int	numchar(char const *s2, char c, int i)
{
	int		lenght;

	lenght = 0;
	while (s2[i] != c && s2[i])
	{
		lenght++;
		i++;
	}
	return (lenght);
}

static char	**free_all(char const **dst, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)dst[j]);
	}
	free(dst);
	return (NULL);
}

static char	**copy(char const *s, char **dst, char c, int l)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[i] && j < l)
	{
		k = 0;
		while (s[i] == c)
			i++;
		dst[j] = (char *)malloc(sizeof(char) * numchar(s, c, i) + 1);
		if (dst[j] == NULL)
			return (free_all((char const **)dst, j));
		while (s[i] && s[i] != c)
			dst[j][k++] = s[i++];
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = 0;
	return (dst);
}

char		**ft_split(char const *s, char c)
{
	char	**dst;
	int		l;

	if (s == NULL)
		return (NULL);
	l = nwords(s, c);
	dst = (char **)malloc(sizeof(char *) * (l + 1));
	if (dst == NULL)
		return (NULL);
	return (copy(s, dst, c, l));
}
