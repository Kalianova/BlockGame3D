#include "cub3d.h"

int		rotatePlayer(t_vars *vars, double x)
{
	double oldDirX = vars->player->dirX;
    vars->player->dirX = vars->player->dirX * cos(x) - vars->player->dirY * sin(x);
    vars->player->dirY = oldDirX * sin(x) + vars->player->dirY * cos(x);
    double oldPlaneX = vars->player->planeX;
    vars->player->planeX = vars->player->planeX * cos(x) - vars->player->planeY * sin(x);
    vars->player->planeY = oldPlaneX * sin(x) + vars->player->planeY * cos(x);
    return (1);
}

int		isPossibleMove(t_vars *vars, double x, double y)
{
	int k;

	k = 0;
	if (!vars->map[(int)vars->player->posX]
		[(int)(vars->player->posY + y * vars->player->moveSpeed)] && y != 0.0)
	{
		k = 1;
      	vars->player->posY += y * vars->player->moveSpeed;
	}
	if (!vars->map[(int)(vars->player->posX + x * vars->player->moveSpeed)]
		[(int)vars->player->posY] && x != 0.0)
	{
		k = 1;
		vars->player->posX += x * vars->player->moveSpeed;
	}
	return (k);
}

int             key_hook(int keycode, t_vars *vars)
{
	int k;

	k = 0;
	if (keycode == KEY_ESC)
	{
    	mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
		exit(0);
	}
	if (keycode == KEY_W)
		k = isPossibleMove(vars, vars->player->dirX, vars->player->dirY);
	if (keycode == KEY_S)
		k = isPossibleMove(vars, -vars->player->dirX, -vars->player->dirY);
	if (keycode == KEY_A)
		k = isPossibleMove(vars, -vars->player->dirY, vars->player->dirX);
	if (keycode == KEY_D)
		k = isPossibleMove(vars, vars->player->dirY, -vars->player->dirX);
	if (keycode == KEY_ARROW_LEFT)
		k = rotatePlayer(vars, vars->player->rotSpeed);
	if (keycode == KEY_ARROW_RIGHT)
		k = rotatePlayer(vars, -vars->player->rotSpeed);
	if (k)
		raysAll(vars, vars->player);
	return (0);
}