/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:41:01 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 19:42:47 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*point;
	int		count;
	void	*dest;

	count = nmemb * size;
	if (!(dest = (void *)malloc(nmemb * size)))
		return (dest);
	point = (char *)dest;
	while (count-- > 0)
		point[count] = 0;
	return (dest);
}
