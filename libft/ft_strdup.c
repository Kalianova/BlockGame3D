/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:04:32 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 20:05:37 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		count;
	char	*dest;

	count = 0;
	while (s[count])
		count++;
	if (!(dest = (char *)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	dest[count] = '\0';
	count = 0;
	while (s[count])
	{
		dest[count] = s[count];
		count++;
	}
	return (dest);
}
