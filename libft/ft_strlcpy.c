/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:09:37 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 20:09:45 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t count;

	count = 0;
	if (!dst || !src)
		return (0);
	while (count + 1 < size && src[count])
	{
		dst[count] = src[count];
		++count;
	}
	if (size != 0)
		dst[count] = '\0';
	while (src[count])
		count++;
	return (count);
}
