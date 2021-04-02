/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:13:14 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 20:13:21 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t count;

	count = 0;
	if (n == 0)
		return (0);
	while (s1[count] == s2[count] && s1[count] && s2[count])
	{
		if (n - count <= 1)
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		count++;
	}
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}
