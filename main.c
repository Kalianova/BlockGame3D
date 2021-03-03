#include "cub3d.h"

int g = 100;


void printParams(t_vars *v)
{
	int i;
	int j;

	i = 0;
	j = 0;
	printf("%i\n", v->w);
	printf("%i\n", v->h);
	printf("%s\n", v->NO);
	printf("%s\n", v->WE);
	printf("%s\n", v->EA);
	printf("%s\n", v->SO);
	printf("%s\n", v->S);
	printf("%i\n", v->F);
	printf("%i\n", v->C);
	while (i < v->rows){
		while (j < v->cols){
			printf("%i", v->map[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}

int             key_hook(int keycode, t_vars *vars)
{
	
	raysAll(vars, vars->player);
	printf("%f %f  ", vars->player->posX, vars->player->posY);
	printf("%d\n", keycode);
	if (keycode == KEY_ESC)
	{
    	mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
		exit(0);
	}
	if (keycode == KEY_W)
	{		vars->player->posX += vars->player->dirX * vars->player->moveSpeed;

      	vars->player->posY += vars->player->dirY * vars->player->moveSpeed;
		/*g++;
		for (int i = 0; i < 400; ++i)
       		line_draw(vars->img_1, vars->img, i, 40, g);
    	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);*/
		return (0);
	}
	if (keycode == KEY_S)
	{
			vars->player->posX -= vars->player->dirX * vars->player->moveSpeed;
      	vars->player->posY -= vars->player->dirY * vars->player->moveSpeed;
		/*g--;
		for (int i = 0; i < 400; ++i)
       		line_draw(vars->img_1, vars->img, i, 40, g);
    	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);*/
		return (0);
	}
	if (keycode == KEY_A)
	{
		 double oldDirX = vars->player->dirX;
      vars->player->dirX = vars->player->dirX * cos(-vars->player->rotSpeed) - vars->player->dirY * sin(-vars->player->rotSpeed);
      vars->player->dirY = oldDirX * sin(-vars->player->rotSpeed) + vars->player->dirY * cos(-vars->player->rotSpeed);
      double oldPlaneX = vars->player->planeX;
      vars->player->planeX = vars->player->planeX * cos(-vars->player->rotSpeed) - vars->player->planeY * sin(-vars->player->rotSpeed);
      vars->player->planeY = oldPlaneX * sin(-vars->player->rotSpeed) + vars->player->planeY * cos(-vars->player->rotSpeed);
	}
	if (keycode == KEY_D)
	{
		double oldDirX = vars->player->dirX;
      vars->player->dirX = vars->player->dirX * cos(vars->player->rotSpeed) - vars->player->dirY * sin(vars->player->rotSpeed);
      vars->player->dirY = oldDirX * sin(vars->player->rotSpeed) + vars->player->dirY * cos(vars->player->rotSpeed);
      double oldPlaneX = vars->player->planeX;
      vars->player->planeX = vars->player->planeX * cos(vars->player->rotSpeed) - vars->player->planeY * sin(vars->player->rotSpeed);
      vars->player->planeY = oldPlaneX * sin(vars->player->rotSpeed) + vars->player->planeY * cos(vars->player->rotSpeed);
	}
	printf("%i\n", keycode);

	return (0);
}

int             key_close(int keycode, t_vars *vars)
{
	printf("sgfgrf\n");
	mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
		exit(0);
	}

t_data get_picture(void *mlx, char *path)
{
	t_data img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.w, &img.h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	return (img);
}

t_player init_player()
{
	t_player player;

	player.posX = 20.0;
	player.posY = 12.0;
	player.dirX = -1;
	player.dirY = 0;
	player.planeX = 0.0;
	player.planeY = 0.66;
	player.moveSpeed = 0.03;
	player.rotSpeed = 0.03;
	return (player);
}

int 	main(void)
{

	void    *mlx;
    void    *mlx_win;
    t_data  img;
    t_data	img_1;

    img.w = 800;
    img.h = 800;
    
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, img.w, img.h, "Hello world!");
    img_1 = get_picture(mlx, "pictures/n.xpm"); //Try to read if not to error
    img.img = mlx_new_image(mlx, img.w, img.h);

    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    for (int i = 0; i < 400; ++i)
       line_draw(&img_1, &img, i, 100);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

    t_vars vars;
    t_player player;
    vars.player = &player;
	parseFile("maps/map2.cub", &vars);
    /*t_vars      vars;
	vars.mlx = mlx;
	vars.win = mlx_win;
	vars.img = &img;
	vars.img_1 = &img_1;

	mlx_key_hook(vars.win, key_hook, &vars);*/
	//mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	//mlx_hook(vars.win, 17, 1L<<17, key_close, &vars);
	/*t_player pl;

	t_player* player  = malloc(sizeof pl);

	player->posX = 20.0;
	player->posY = 12.0;
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0.0;
	player->planeY = 0.66;
	player->moveSpeed = 0.03;
	player->rotSpeed = 0.03;

	vars.player = player;
	printf("------%i %i  ", vars.player->posX, vars.player->posY);
	int map[24][24]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};
		int **A = (int **)malloc(24*sizeof(int *));
for(int i = 0; i < 24; i++) {
    A[i] = (int *)malloc(24*sizeof(int));
    for (int j = 0; j < 24; j++){
    	A[i][j] = map[i][j];
    }
}
	vars.map = A;
    printf("------%i %i  ", vars.player->posX, vars.player->posY);
	raysAll(&vars, &player);
printf("-----%i %i  ", vars.player->posX, vars.player->posY);*/


    mlx_loop(mlx);
}