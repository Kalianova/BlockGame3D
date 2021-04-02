/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:21:27 by astaryu           #+#    #+#             */
/*   Updated: 2021/03/26 14:21:42 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "fcntl.h"

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ARROW_LEFT 123
# define KEY_ARROW_RIGHT 124

typedef struct		s_sprite
{
	int				x;
	int				y;
}					t_sprite;

typedef struct		s_sprite_info
{
	double			x;
	double			y;
	int				width;
	int				height;
	double			invDet;
	double			transf_x;
	double			transf_y;
	int				spriteScreenX;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
}					t_sprite_info;

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				w;
	int				h;
}					t_data;

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			r_dir_x;
	double			r_dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
}					t_player;

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
	int				w;
	int				h;
	t_data			*img;
	t_data			we;
	t_data			ea;
	t_data			no;
	t_data			so;
	t_data			s;
	unsigned int	f;
	unsigned int	c;
	t_list			*sprite;
	int				rows;
	int				cols;
	int				**map;
	t_player		*player;
}					t_vars;

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					my_mlx_pixel_get(t_data *data, int x, int y);
int					parse_file(char *name_of_file, t_vars *v);
int					key_hook(int keycode, t_vars *vars);
int					key_close(int keycode, t_vars *vars);
void				sprites(t_vars *v, double **buf);
int					parse_map(t_vars *v, t_list **head);
int					errors(char *message, char ***del);
t_data				*choose_side(t_vars *mlx, int side);
void				line_draw(int x, t_vars *v, double wall_dist, int side);
void				put_in_sprites(t_vars *mlx, int x, int y);
void				ray_put(t_vars *mlx, int x, double **buf);
void				rays_all(t_vars *mlx, t_player *player, int bmp);
int					parse_one_texture(t_list **head, char **path);
unsigned int		parse_one_colors
(t_list **head, char *name, unsigned int *res);
int					parse_window_size(t_vars *v, t_list **head);
t_data				get_picture(void *mlx, char *path);
int					next_line(t_list **head);
void				switch_texture(t_vars *v, char **param, char **path);
int					check_num(char *s);
int					save_bmp(t_vars *v);
void				erase_array_int(int ***del);
void				delete_all(t_vars *v);

#endif
