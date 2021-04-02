/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:01:54 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 20:02:05 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	count;
	char		c;

	count = 1;
	if (n == 0)
		write(fd, "0", 1);
	while (n / count != 0)
		count *= 10;
	count /= 10;
	if (n < 0)
	{
		write(fd, "-", 1);
		count *= -1;
	}
	while (count != 0)
	{
		c = n / count + '0';
		write(fd, &c, 1);
		n = n % count;
		count /= 10;
	}
}
