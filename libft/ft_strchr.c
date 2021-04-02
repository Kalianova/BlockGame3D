/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:04:07 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 20:04:14 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *pointer;

	pointer = (char *)s;
	while (*pointer)
	{
		if (*pointer == c)
			return (pointer);
		++pointer;
	}
	if (*pointer == c)
		return (pointer);
	return (NULL);
}
