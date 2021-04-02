/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:05:48 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 20:08:25 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if ((res = (char *)malloc((i + j + 1) * sizeof(char))) == NULL)
		return (NULL);
	res[i + j] = '\0';
	while (j > 0)
	{
		--j;
		res[i + j] = s2[j];
	}
	while (i > 0)
	{
		--i;
		res[i] = s1[i];
	}
	return (res);
}
