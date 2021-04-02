/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 19:30:51 by astaryu           #+#    #+#             */
/*   Updated: 2021/04/02 19:30:52 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//sega and cleaning
//what if we can't read sprite
//check map parsing
//makefile
//comments in main. and key_hook.c

void	delete_all(t_vars *v)
{
	erase_array_int(&(v->map));
	//mlx_destroy_window(vars->mlx, vars->win); //sega
	if (v->we.img)
		free(v->we.img);
	if (v->ea.img)
		free(v->ea.img);
	if (v->no.img)
		free(v->no.img);
	if (v->so.img)
		free(v->so.img);
	exit(0);
}

void	init_vars(t_vars *vars, t_player *player)
{
	vars->mlx = mlx_init();
	player->pos_x = -1.0;
	player->pos_y = -1.0;
	vars->player = player;
	vars->we.img = NULL;
	vars->ea.img = NULL;
	vars->no.img = NULL;
	vars->so.img = NULL;
}

int		main(int argc, char **argv)
{
	t_vars		vars;
	t_data		img;
	t_player	player;

	init_vars(&vars, &player);
	if (argc < 2)
		return (errors("No parameter of map\n", NULL));
	if (!parse_file(argv[1], &vars))
		key_close(1, &vars);
	vars.win = mlx_new_window(vars.mlx, vars.w, vars.h, "Hello world!");
	img.img = mlx_new_image(vars.mlx, vars.w, vars.h);
	img.w = vars.w;
	img.h = vars.h;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	&img.line_length, &img.endian);
	vars.img = &img;
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
		rays_all(&vars, vars.player, 1);
	rays_all(&vars, vars.player, 0);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 1L << 17, key_close, &vars);
	mlx_loop(vars.mlx);
}
