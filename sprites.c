/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 19:21:10 by astaryu           #+#    #+#             */
/*   Updated: 2021/04/02 19:21:11 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite(t_vars *v, t_sprite_info *sp_inf, double **buf,
int sprite_x)
{
	int				temp;
	int				tex_x;
	int				tex_y;
	int				d;
	unsigned int	color;

	while (sp_inf->draw_start_x++ < sp_inf->draw_end_x)
	{
		tex_x = (int)(256 * (sp_inf->draw_start_x - 1 - (-sp_inf->width / 2 +
		sprite_x)) * v->s.w / sp_inf->width) / 256;
		temp = sp_inf->draw_start_y;
		if (sp_inf->transf_y > 0 && v->w - sp_inf->draw_start_x - 1 >= 0 &&
		v->w - sp_inf->draw_start_x - 1 < v->w && sp_inf->transf_y <
		*(*buf + sp_inf->draw_start_x))
			while (temp++ < sp_inf->draw_end_y)
			{
				d = (temp - 1) * 256 - v->h * 128 + sp_inf->height * 128;
				tex_y = ((d * v->s.h) / sp_inf->height) / 256;
				color = my_mlx_pixel_get(&v->s, tex_x, tex_y);
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(v->img, v->w - sp_inf->draw_start_x - 1,
					temp - 1, color);
			}
	}
}

void	sprites_add(t_vars *v, t_sprite_info *sp_inf, int sprite_x)
{
	sp_inf->draw_start_y = -sp_inf->height / 2 + v->h / 2;
	if (sp_inf->draw_start_y < 0)
		sp_inf->draw_start_y = 0;
	sp_inf->draw_end_y = sp_inf->height / 2 + v->h / 2;
	if (sp_inf->draw_end_y >= v->h)
		sp_inf->draw_end_y = v->h - 1;
	sp_inf->width = abs((int)(v->h / (sp_inf->transf_y)));
	sp_inf->draw_start_x = -sp_inf->width / 2 + sprite_x;
	if (sp_inf->draw_start_x < 0)
		sp_inf->draw_start_x = 0;
	sp_inf->draw_end_x = sp_inf->width / 2 + sprite_x;
	if (sp_inf->draw_end_x >= v->w)
		sp_inf->draw_end_x = v->w - 1;
}

void	sprites(t_vars *v, double **buf)
{
	t_sprite_info	sp_inf;
	double			inv_det;
	int				sprite_screen_x;
	t_list			*tmp;

	while (v->sprite)
	{
		sp_inf.x = ((t_sprite *)v->sprite->content)->x + 0.5 - v->player->pos_x;
		sp_inf.y = ((t_sprite *)v->sprite->content)->y + 0.5 - v->player->pos_y;
		inv_det = 1.0 / (v->player->plane_x * v->player->dir_y -
		v->player->dir_x * v->player->plane_y);
		sp_inf.transf_x = inv_det * (v->player->dir_y * sp_inf.x -
		v->player->dir_x * sp_inf.y);
		sp_inf.transf_y = inv_det * (-v->player->plane_y * sp_inf.x +
		v->player->plane_x * sp_inf.y);
		sprite_screen_x = (int)((v->w / 2) * (1 + sp_inf.transf_x /
		sp_inf.transf_y));
		sp_inf.height = abs((int)(v->h / (sp_inf.transf_y)));
		sprites_add(v, &sp_inf, sprite_screen_x);
		draw_sprite(v, &sp_inf, buf, sprite_screen_x);
		free(v->sprite->content);
		tmp = v->sprite;
		v->sprite = v->sprite->next;
		free(tmp);
	}
}
