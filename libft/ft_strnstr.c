/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:13:40 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 20:14:12 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*pointer;
	size_t	n;

	pointer = (char *)big;
	if (*little == '\0')
		return (pointer);
	while (*pointer && len > 0)
	{
		n = 0;
		while (pointer[n] == little[n] && pointer[n] && little[n] && len != n)
			n++;
		if (little[n] == '\0')
			return (pointer);
		++pointer;
		--len;
	}
	return (NULL);
}
