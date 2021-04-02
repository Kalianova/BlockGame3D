/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:14:30 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 20:14:38 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *pointer;
	char *result;

	result = NULL;
	pointer = (char *)s;
	while (*pointer)
	{
		if (*pointer == c)
			result = pointer;
		++pointer;
	}
	if (*pointer == c)
		return (pointer);
	return (result);
}
