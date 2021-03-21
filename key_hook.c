#include "cub3d.h"

int		key_close(int keycode, t_vars *vars)
{
	if (vars == NULL)
	{
		exit(0);
	}
	return (keycode);
}

int		rotate_player(t_vars *vars, double x)
{
	double dir_x;
	double dir_y;
	double old_dir_x;
	double old_plane_x;

	dir_x = vars->player->dirX;
	dir_y = vars->player->dirY;
	old_dir_x = dir_x;
	vars->player->dirX = dir_x * cos(x) - dir_y * sin(x);
	vars->player->dirY = old_dir_x * sin(x) + dir_y * cos(x);
	old_plane_x = vars->player->planeX;
	vars->player->planeX = vars->player->planeX * cos(x)
	- vars->player->planeY * sin(x);
	vars->player->planeY = old_plane_x * sin(x)
	+ vars->player->planeY * cos(x);
	return (1);
}

int		is_possible_move(t_vars *vars, double x, double y)
{
	int k;

	k = 0;
	if (vars->map[(int)vars->player->posX]
		[(int)(vars->player->posY + y * (vars->player->moveSpeed) + 0.2)] != 1
		&& vars->map[(int)vars->player->posX]
		[(int)(vars->player->posY + y * (vars->player->moveSpeed) - 0.2)] != 1
		&& y != 0.0)
	{
		k = 1;
		vars->player->posY += y * vars->player->moveSpeed;
	}
	if (vars->map[(int)(vars->player->posX + x * (vars->player->moveSpeed)
		+ 0.2)][(int)vars->player->posY] != 1 && vars->map[(int)
		(vars->player->posX + x * (vars->player->moveSpeed) - 0.2)]
		[(int)vars->player->posY] != 1 && x != 0.0)
	{
		k = 1;
		vars->player->posX += x * vars->player->moveSpeed;
	}
	return (k);
}

int		key_hook(int keycode, t_vars *vars)
{
	int k;

	k = 0;
	if (keycode == KEY_ESC)
	{
		deleteAll(vars);
		mlx_destroy_window(vars->mlx, vars->win);
		//exit(0);
	}
	if (keycode == KEY_W)
		k = is_possible_move(vars, vars->player->dirX, vars->player->dirY);
	if (keycode == KEY_S)
		k = is_possible_move(vars, -vars->player->dirX, -vars->player->dirY);
	if (keycode == KEY_A)
		k = is_possible_move(vars, -vars->player->dirY, vars->player->dirX);
	if (keycode == KEY_D)
		k = is_possible_move(vars, vars->player->dirY, -vars->player->dirX);
	if (keycode == KEY_ARROW_LEFT)
		k = rotate_player(vars, vars->player->rotSpeed);
	if (keycode == KEY_ARROW_RIGHT)
		k = rotate_player(vars, -vars->player->rotSpeed);
	if (k)
		rays_all(vars, vars->player);
	return (0);
}
