/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:02:45 by astaryu           #+#    #+#             */
/*   Updated: 2020/11/04 12:34:53 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	long long	count;
	char		*point;

	count = 0;
	point = (char *)s;
	while (*point == c && *point)
		++point;
	if (c == '\0' && *point)
		return (1);
	if (!(*point))
		return (0);
	while (*point)
	{
		while (*point != c && *point)
			++point;
		count++;
		while (*point == c && *point)
			++point;
	}
	return (count);
}

static char	*make_word(char const *s, int *begin, char c)
{
	int j;

	j = 0;
	while (s[*begin] == c && s[*begin])
		(*begin)++;
	while (s[(*begin) + j] != c && s[(*begin) + j])
		j++;
	(*begin) += j;
	return (ft_substr(s, (*begin) - j, j));
}

char		**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	int		arr;
	char	**res;

	i = 0;
	arr = -1;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	if (!(res = (char **)malloc((words + 1) * sizeof(char *))))
		return (NULL);
	while (++arr < words)
	{
		res[arr] = make_word(s, &i, c);
		if (!res[arr])
		{
			while (--arr >= 0)
				free(res[arr]);
			free(res);
		}
	}
	res[words] = NULL;
	return (res);
}
