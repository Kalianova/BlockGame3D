#include "cub3d.h"

//--save
//screen size if size more then needed

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
   
    t_player player;
    player.posX = -1.0;
    player.posY = -1.0;
    vars.player = &player; 
    if (!parseFile("maps/map1.cub", &vars)){
    	deleteAll();
    	key_close(1, &vars);
    }

    mlx_win = mlx_new_window(vars.mlx, vars.w, vars.h, "Hello world!");
     vars.win = mlx_win;
    img.img = mlx_new_image(mlx, vars.w, vars.h);
    img.w = vars.w;
    img.h = vars.h;

    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
    	&img.line_length, &img.endian);
	vars.img = &img;
    mlx_put_image_to_window(mlx, mlx_win, vars.img->img, 0, 0);
    raysAll(&vars, vars.player);

	//mlx_key_hook(mlx_win, key_hook, &vars);
	mlx_hook(mlx_win, 2, 1L<<0, key_hook, &vars);
	mlx_hook(mlx_win, 17, 1L<<17, key_close, &vars);

    mlx_loop(mlx);
}