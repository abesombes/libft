/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesombe <abesombe@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 22:35:27 by abesombe          #+#    #+#             */
/*   Updated: 2020/11/23 18:23:41 by abesombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j > 0)
			count++;
		i = i + j;
	}
	return (count);
}

static char	**ft_free_memory(char **strs, int index)
{
	while (--index >= 0)
		free(strs[index]);
	free(strs);
	return (NULL);
}

static int	ft_index_next_c(const char *src, char c, int limit)
{
	int i;

	i = 0;
	while (src[i] && i <= limit)
	{
		if (src[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char	**ft_copy_to_strs(char **strs, const char *src, char sep,\
		int nb_words)
{
	int index;
	int size;
	int i;

	index = 0;
	while (index < nb_words)
	{
		size = 0;
		while (*src && ft_index_next_c(src, sep, 0) >= 0)
			src++;
		while (*(src + size) && ft_index_next_c(src, sep, size) < 0)
			size++;
		if (!(strs[index] = (char *)malloc(sizeof(char) * (size + 1))))
			return (ft_free_memory(strs, index));
		i = -1;
		while (++i < size)
			strs[index][i] = src[i];
		strs[index][i] = '\0';
		src = src + size;
		index++;
	}
	strs[index] = 0;
	return (strs);
}

char		**ft_split(char const *s, char c)
{
	char	**strs;
	int		count_wd;

	if (!s)
		return (NULL);
	count_wd = ft_count_words(s, c);
	if (!(strs = (char **)malloc((count_wd + 1) * sizeof(char *))))
		return (NULL);
	return (ft_copy_to_strs(strs, s, c, count_wd));
}
