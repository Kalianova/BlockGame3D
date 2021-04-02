/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:14:54 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 20:15:15 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int begin;
	int end;
	int len;

	begin = -1;
	end = -1;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[++begin] && set[0])
		if (!ft_strchr(set, s1[begin]))
			break ;
	while (len - 1 - ++end > 0 && begin != len)
		if (!ft_strchr(set, s1[len - 1 - end]))
			break ;
	return (ft_substr(s1, begin, len - end - begin));
}
