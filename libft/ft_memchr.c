/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:58:47 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 19:58:52 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *pointer;

	pointer = (unsigned char *)s;
	while (n > 0)
	{
		if (*pointer == (unsigned char)c)
			return (pointer);
		++pointer;
		n--;
	}
	return (NULL);
}
