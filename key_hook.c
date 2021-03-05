#include "cub3d.h"

void		rotatePlayer(t_vars *vars, double x)
{
	double oldDirX = vars->player->dirX;
    vars->player->dirX = vars->player->dirX * cos(x) - vars->player->dirY * sin(x);
    vars->player->dirY = oldDirX * sin(x) + vars->player->dirY * cos(x);
    double oldPlaneX = vars->player->planeX;
    vars->player->planeX = vars->player->planeX * cos(x) - vars->player->planeY * sin(x);
    vars->player->planeY = oldPlaneX * sin(x) + vars->player->planeY * cos(x);
}

void		isPossibleMove(t_vars *vars, double x, double y)
{
	if (!vars->map[(int)vars->player->posX]
		[(int)(vars->player->posY + y * vars->player->moveSpeed)])
	{
      	vars->player->posY += y * vars->player->moveSpeed;
	}
	if (!vars->map[(int)(vars->player->posX + x * vars->player->moveSpeed)]
		[(int)vars->player->posY])
	{
		vars->player->posX += x * vars->player->moveSpeed;
	}
}

int             key_hook(int keycode, t_vars *vars)
{
	printf("%i %f, %f, %f, %f\n", keycode, vars->player->posX, vars->player->posY, vars->player->dirX, vars->player->dirY);
	//fflush(stdout);
	if (keycode == KEY_ESC)
	{
    	mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
		exit(0);
	}
	if (keycode == KEY_W)
		isPossibleMove(vars, vars->player->dirX, vars->player->dirY);
	if (keycode == KEY_S)
		isPossibleMove(vars, -vars->player->dirX, -vars->player->dirY);
	if (keycode == KEY_A)
		isPossibleMove(vars, -vars->player->dirY, -vars->player->dirX);
	if (keycode == KEY_D)
		isPossibleMove(vars, vars->player->dirY, vars->player->dirX);
	if (keycode == KEY_ARROW_LEFT)
		rotatePlayer(vars, -vars->player->rotSpeed);
	if (keycode == KEY_ARROW_RIGHT)
		rotatePlayer(vars, vars->player->rotSpeed);
	return (0);
}