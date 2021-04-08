/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 18:16:34 by astaryu           #+#    #+#             */
/*   Updated: 2021/04/02 18:16:38 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_put_add_y(double *dist, int *step, double *delta, t_player *player)
{
	if (player->r_dir_x == 0)
		*delta = 0;
	else if (player->r_dir_y == 0)
		*delta = 1;
	else
		*delta = fabs(1 / player->r_dir_y);
	if (player->r_dir_y < 0)
	{
		*step = -1;
		*dist = (player->pos_y - (int)player->pos_y) * *delta;
	}
	else
	{
		*step = 1;
		*dist = ((int)player->pos_y + 1.0 - player->pos_y) * *delta;
	}
}

void	ray_put_add_x(double *dist, int *step, double *delta, t_player *player)
{
	if (player->r_dir_y == 0)
		*delta = 0;
	else if (player->r_dir_x == 0)
		*delta = 1;
	else
		*delta = fabs(1 / player->r_dir_x);
	if (player->r_dir_x < 0)
	{
		*step = -1;
		*dist = (player->pos_x - (int)player->pos_x) * *delta;
	}
	else
	{
		*step = 1;
		*dist = ((int)player->pos_x + 1.0 - player->pos_x) * *delta;
	}
}

t_data	*choose_side(t_vars *mlx, int side)
{
	t_data *src;

	if (side == 0)
	{
		if (mlx->player->r_dir_x < 0)
			src = &mlx->no;
		else
			src = &mlx->so;
	}
	else
	{
		if (mlx->player->r_dir_y < 0)
			src = &mlx->we;
		else
			src = &mlx->ea;
	}
	return (src);
}

double	choose_wall_dist(int side, int map, int step, t_vars *v)
{
	double wall_dist;

	wall_dist = (map + (1 - step) / 2);
	if (side == 0)
		return (wall_dist - v->player->pos_x) / v->player->r_dir_x;
	else
		return (wall_dist - v->player->pos_y) / v->player->r_dir_y;
}

void	ray_put(t_vars *v, int x, double **buf)
{
	double	dist[2];
	int		step[2];
	double	delta_dist[2];
	int		side;
	int		map[2];

	map[0] = (int)v->player->pos_x;
	map[1] = (int)v->player->pos_y;
	ray_put_add_x(&dist[0], &step[0], &delta_dist[0], v->player);
	ray_put_add_y(&dist[1], &step[1], &delta_dist[1], v->player);
	while (v->map[map[0]][map[1]] != 1)
	{
		if (dist[0] < dist[1])
			side = 0;
		else
			side = 1;
		dist[side] += delta_dist[side];
		map[side] += step[side];
		if (v->map[map[0]][map[1]] == 2)
			put_in_sprites(v, map[0], map[1]);
	}
	line_draw(v->img->w - x - 1, v,
	choose_wall_dist(side, map[side], step[side], v), side);
	((*buf)[x]) = choose_wall_dist(side, map[side], step[side], v);
}
