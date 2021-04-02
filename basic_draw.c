/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 18:27:50 by astaryu           #+#    #+#             */
/*   Updated: 2021/04/02 18:27:53 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		my_mlx_pixel_get(t_data *data, int x, int y)
{
	char			*dst;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	dst = data->addr +
	(y * data->line_length + x * (data->bits_per_pixel / 8));
	b = dst[0];
	g = dst[1];
	r = dst[2];
	return (r << 16 | g << 8 | b);
}

int		tex_x(t_data *image, t_player *player, int side, double wall_dist)
{
	double	wall_x;
	int		tex_x;

	if (side == 0)
		wall_x = player->pos_y + wall_dist * player->r_dir_y;
	else
		wall_x = player->pos_x + wall_dist * player->r_dir_x;
	wall_x -= (int)wall_x;
	tex_x = (int)(wall_x * (double)(image->w));
	if (side == 0 && player->r_dir_x > 0)
		tex_x = (image->w) - tex_x - 1;
	if (side == 1 && player->r_dir_y < 0)
		tex_x = (image->w) - tex_x - 1;
	return (tex_x);
}

void	line_draw(int x, t_vars *v, double wall_dist, int side)
{
	double				coef;
	long long int		horizont;
	long long int		height;
	int					i;

	height = llabs((int)(v->img->h / wall_dist));
	horizont = v->img->h / 2 - height / 2;
	if (horizont < -1000000)
		return ;
	coef = (choose_side(v, side)->h - 1) / (height + 0.0);
	i = -1;
	while (++i < horizont)
		my_mlx_pixel_put(v->img, x, i, v->c);
	i = horizont + height;
	while (i < v->img->h)
	{
		my_mlx_pixel_put(v->img, x, i, v->f);
		i++;
	}
	height++;
	while (--height > 0)
		if (horizont + height < v->h && horizont + height >= 0)
			my_mlx_pixel_put(v->img, x, horizont + height,
			my_mlx_pixel_get(choose_side(v, side), tex_x(choose_side(v, side),
			v->player, side, fabs(wall_dist)), (int)(coef * height)));
}
