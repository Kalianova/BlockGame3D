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

int             key_close(int keycode, t_vars *vars)
{
	printf("sgfgrf\n");
	mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
		exit(0);
}

void deleteAll()
{
	//make this method
}

int 	main(void)
{

	void    *mlx;
    void    *mlx_win;
    t_vars vars;
    t_data img;
    
    mlx = mlx_init();
    vars.mlx = mlx;
    vars.win = mlx_win;
    t_player player;
    player.posX = -1.0;
    player.posY = -1.0;
    vars.player = &player; 
    if (!parseFile("maps/map1.cub", &vars)){
    	deleteAll();
    	key_close(1, &vars);
    }

    mlx_win = mlx_new_window(vars.mlx, vars.w, vars.h, "Hello world!");
    img.img = mlx_new_image(mlx, vars.w, vars.h);
    img.w = vars.w;
    img.h = vars.h;

    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
    	&img.line_length, &img.endian);
	vars.img = &img;

    for (int i = 0; i < 400; ++i){
       line_draw(&vars.WE, vars.img, i, 200, &vars);
    }

    mlx_put_image_to_window(mlx, mlx_win, vars.img->img, 0, 0);
    //raysAll(&vars, vars.player);
    
	//mlx_key_hook(mlx_win, key_hook, &vars);
	mlx_hook(mlx_win, 2, 1L<<0, key_hook, &vars);
	printf("1");
	fflush(stdout);
	//mlx_hook(vars.win, 17, 1L<<17, key_close, &vars);

    mlx_loop(mlx);
}