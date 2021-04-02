/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:08:59 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 20:09:18 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t count;
	size_t i;

	count = 0;
	i = 0;
	while (dst[i] && i < size)
		++i;
	while (count + 1 + i < size && src[count])
	{
		dst[i + count] = src[count];
		++count;
	}
	if (size != 0 && i != size)
		dst[i + count] = '\0';
	while (src[count])
		count++;
	return (i + count);
}
