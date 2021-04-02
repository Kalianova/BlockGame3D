/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:59:13 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 19:59:19 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *first;
	unsigned char *second;

	first = (unsigned char *)s1;
	second = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 1)
	{
		if (*first != *second)
			return (*first - *second);
		++first;
		++second;
		--n;
	}
	return (*first - *second);
}
