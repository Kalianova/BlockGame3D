#include "cub3d.h"

//--save
//what if we can't read sprite
//parse input map file

void deleteAll(t_vars *v)
{
	erase_array_int(&(v->map));
    free(v->WE.img);
    free(v->EA.img);
    free(v->NO.img);
    free(v->SO.img);
}

int 	main(int argc, char **argv)
{
	void    *mlx;
    void    *mlx_win;
    t_vars	vars;
    t_data	img;
    
    mlx = mlx_init();
    vars.mlx = mlx;
    t_player player;
    player.posX = -1.0;
    player.posY = -1.0;
    vars.player = &player; 
    if (!parse_file("maps/map1.cub", &vars)){
    	deleteAll(&vars);
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
    rays_all(&vars, vars.player);
	if (argc == 2 && ft_strncmp(argv[1], "--save", 6) == 0)
    	save_bmp(&vars);
	//mlx_key_hook(mlx_win, key_hook, &vars);
	mlx_hook(mlx_win, 2, 1L<<0, key_hook, &vars);
	mlx_hook(mlx_win, 17, 1L<<17, key_close, &vars);
    mlx_loop(mlx);

}