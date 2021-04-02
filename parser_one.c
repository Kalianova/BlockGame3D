/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:47:37 by astaryu           #+#    #+#             */
/*   Updated: 2021/03/26 14:47:49 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			erase_array(char ***del)
{
	int i;

	i = -1;
	while ((*del)[++i])
		free((*del)[i]);
	free(*del);
}

void			erase_array_int(int ***del)
{
	int i;

	i = -1;
	if (*del)
	{
		while ((*del)[++i])
			free((*del)[i]);
		free(*del);
	}
}

unsigned int	parse_one_colors(t_list **head, char *name, unsigned int *res)
{
	char			**tmp;
	long long		r;
	long long		g;
	long long		b;

	r = 0;
	b = 0;
	g = 0;
	if (*head && (tmp = ft_split((*head)->content, ',')) &&
		tmp[0] && tmp[1] && tmp[2] && !tmp[3])
	{
		if (!next_line(head))
			return (errors("Not enough parameters", &tmp));
		if (ft_strncmp(tmp[0], name, 1) == 0 && ((g = check_num(tmp[1])) < 0
			|| g > 255 || ((b = check_num(tmp[2])) < 0) || b > 255 ||
			(r = check_num(tmp[0] + 1)) < 0 || r > 255))
			return (errors("Invalid number in color rgb", &tmp));
		*res = (((unsigned char)r) << 16 | ((unsigned char)g) << 8
		| ((unsigned char)b));
		erase_array(&tmp);
		return (1);
	}
	return (errors("Invalid color parameters", &tmp));
}

int				parse_one_texture(t_list **head, char **path)
{
	char	**tmp;
	int		fd;

	if (*head && (tmp = ft_split((*head)->content, ' ')) &&
		tmp[0] && tmp[1] && !tmp[2])
	{
		*path = ft_strdup(tmp[1]);
		if (!next_line(head))
			return (errors("Not enough parameters", &tmp));
		fd = open(tmp[1], O_RDONLY);
		if (fd < 0)
			return (errors("No texture file", &tmp));
		erase_array(&tmp);
		return (1);
	}
	return (errors("Invalid texture parameters", &tmp));
}

int				parse_window_size(t_vars *v, t_list **head)
{
	char	**tmp;
	int		size[2];

	mlx_get_screen_size(v->mlx, &size[0], &size[1]);
	if (*head)
	{
		tmp = ft_split((*head)->content, ' ');
		if (tmp[1] && ft_isdigit(tmp[1][0]) && tmp[2]
			&& ft_isdigit(tmp[2][0]) && !tmp[3])
		{
			if ((v->w = check_num(tmp[1])) < 0
				|| (v->h = check_num(tmp[2])) < 0)
				return (errors("Invalid number in R parameter", &tmp));
		}
		else
			return (errors("Invalid number of parameters in R", &tmp));
		erase_array(&tmp);
		if (!next_line(head))
			return (errors("Invalid number of parameters)", NULL));
	}
	if (v->w > size[0])
		v->w = size[0];
	if (v->h > size[1])
		v->h = size[1];
	return (1);
}
