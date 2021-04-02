/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:58:11 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 19:58:31 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest_point;
	unsigned char	*src_point;

	dest_point = (unsigned char *)dest;
	src_point = (unsigned char *)src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		dest_point[i] = src_point[i];
		if (src_point[i] == (unsigned char)c)
			return (dest + i + 1);
		++i;
	}
	return (NULL);
}
