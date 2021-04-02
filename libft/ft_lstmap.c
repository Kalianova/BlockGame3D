/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:56:01 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 19:56:43 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *res;
	t_list *point;

	res = NULL;
	if (!lst || !f || !(res = ft_lstnew(f(lst->content))))
		return (NULL);
	point = res;
	while (lst->next)
	{
		lst = lst->next;
		if (!(res->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&point, del);
			return (NULL);
		}
		res = res->next;
	}
	return (point);
}
