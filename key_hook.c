/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:46:12 by astaryu           #+#    #+#             */
/*   Updated: 2021/03/26 14:46:16 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_close(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win); //sega
	exit(0);
	return (keycode);
}

int		rotate_player(t_vars *vars, double x)
{
	double dir_x;
	double dir_y;
	double old_dir_x;
	double old_plane_x;

	dir_x = vars->player->dir_x;
	dir_y = vars->player->dir_y;
	old_dir_x = dir_x;
	vars->player->dir_x = dir_x * cos(x) - dir_y * sin(x);
	vars->player->dir_y = old_dir_x * sin(x) + dir_y * cos(x);
	old_plane_x = vars->player->plane_x;
	vars->player->plane_x = vars->player->plane_x * cos(x)
	- vars->player->plane_y * sin(x);
	vars->player->plane_y = old_plane_x * sin(x)
	+ vars->player->plane_y * cos(x);
	return (1);
}

int		is_possible_move(t_vars *vars, double x, double y)
{
	int k;

	k = 0;
	if (vars->map[(int)vars->player->pos_x]
		[(int)(vars->player->pos_y + y * (vars->player->move_speed) + 0.2)] != 1
		&& vars->map[(int)vars->player->pos_x]
		[(int)(vars->player->pos_y + y * (vars->player->move_speed) - 0.2)] != 1
		&& y != 0.0)
	{
		k = 1;
		vars->player->pos_y += y * vars->player->move_speed;
	}
	if (vars->map[(int)(vars->player->pos_x + x * (vars->player->move_speed)
		+ 0.2)][(int)vars->player->pos_y] != 1 && vars->map[(int)
		(vars->player->pos_x + x * (vars->player->move_speed) - 0.2)]
		[(int)vars->player->pos_y] != 1 && x != 0.0)
	{
		k = 1;
		vars->player->pos_x += x * vars->player->move_speed;
	}
	return (k);
}

int		key_hook(int keycode, t_vars *vars)
{
	int k;

	k = 0;
	if (keycode == KEY_ESC)
	{
		delete_all(vars);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == KEY_W)
		k = is_possible_move(vars, vars->player->dir_x, vars->player->dir_y);
	if (keycode == KEY_S)
		k = is_possible_move(vars, -vars->player->dir_x, -vars->player->dir_y);
	if (keycode == KEY_A)
		k = is_possible_move(vars, -vars->player->dir_y, vars->player->dir_x);
	if (keycode == KEY_D)
		k = is_possible_move(vars, vars->player->dir_y, -vars->player->dir_x);
	if (keycode == KEY_ARROW_LEFT)
		k = rotate_player(vars, vars->player->rot_speed);
	if (keycode == KEY_ARROW_RIGHT)
		k = rotate_player(vars, -vars->player->rot_speed);
	if (k)
		rays_all(vars, vars->player, 0);
	return (0);
}
