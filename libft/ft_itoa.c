/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:48:32 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 19:50:04 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_number(int n)
{
	int i;

	i = 1;
	if (n == 0)
		return (1);
	if (n < 0)
		++i;
	while (n / 10 != 0)
	{
		++i;
		n /= 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*res;

	i = count_number(n);
	if ((res = (char *)malloc((i + 1) * sizeof(char))) == NULL)
		return (NULL);
	res[i] = '\0';
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		res[--i] = n % 10 * (-1) + '0';
		n = n / 10 * (-1);
	}
	while (n != 0)
	{
		res[--i] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}
