/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:01:27 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 20:01:32 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int count;

	count = 0;
	if (s != NULL)
	{
		while (s[count])
		{
			write(fd, &s[count], 1);
			++count;
		}
		write(fd, "\n", 1);
	}
}
