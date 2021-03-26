#include "cub3d.h"

//--save
//what if we can't read sprite
//parse input map file
//check map parsing

void delete_all(t_vars *v)
{
	erase_array_int(&(v->map));
    free(v->we.img);
    free(v->ea.img);
    free(v->no.img);
    free(v->so.img);
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
    player.pos_x = -1.0;
    player.pos_y = -1.0;
    vars.player = &player; 
    if (argc < 2)
        return (errors("No parameter of map\n", NULL));
    if (!parse_file(argv[1], &vars)){
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
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
    	rays_all(&vars, vars.player, 1);
    rays_all(&vars, vars.player, 0);
	//mlx_key_hook(mlx_win, key_hook, &vars);
	mlx_hook(mlx_win, 2, 1L<<0, key_hook, &vars);
	mlx_hook(mlx_win, 17, 1L<<17, key_close, &vars);
    mlx_loop(mlx);

}