/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:59:33 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 19:59:39 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char *dest_point;
	char *src_point;

	dest_point = (char *)dest;
	src_point = (char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n > 0)
	{
		*dest_point = *src_point;
		dest_point++;
		src_point++;
		n--;
	}
	return (dest);
}
