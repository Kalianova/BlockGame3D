/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:59:52 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 19:59:59 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			count;
	unsigned char	*dest_point;
	unsigned char	*src_point;

	count = 0;
	dest_point = (unsigned char *)dest;
	src_point = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest_point < src_point)
		while (count < n)
		{
			dest_point[count] = src_point[count];
			++count;
		}
	else
		while (n > 0)
		{
			--n;
			dest_point[n] = src_point[n];
		}
	return (dest);
}
