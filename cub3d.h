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
# define KEY_W 13 //119 //13 
# define KEY_A 0 //97 // 0 
# define KEY_S 1 //115 //1 
# define KEY_D 2 //100 //2 
# define KEY_ARROW_LEFT 123 //65361 //123 
# define KEY_ARROW_RIGHT 124 //65363 //124

typedef struct 		s_sprite
{
	int				x;
	int				y;
}					t_sprite;

typedef struct  	s_data 
{
    void			*img;
    char			*addr;
    int				bits_per_pixel;
    int				line_length;
    int				endian;
    int				w;
    int				h;
}               t_data;

typedef struct 		s_player 
{
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			rayDirX;
	double			rayDirY;
	double 			planeX;
	double			planeY;
	double			moveSpeed;
	double			rotSpeed;
}					t_player;

typedef struct  	s_vars 
{
    void        	*mlx;
    void        	*win;
    int				w;
    int				h;
    t_data			*img;
    t_data			WE;
	t_data			EA;
	t_data			NO;
	t_data			SO;
	t_data 			S;
	unsigned int	F;
	unsigned int	C;
	t_list			*sprite;
	int 			rows;
	int				cols;
    int				**map;
    t_player		*player;
}               	t_vars;
	
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					my_mlx_pixel_get(t_data *data, int x, int y);
int					parse_file(char *name_of_file, t_vars *v);
int					key_hook(int keycode, t_vars *vars);
int					key_close(int keycode, t_vars *vars);
void				sprites(t_vars *v, double **buf);
int					parse_map(t_vars *v, t_list **head);
int					errors(char *message, char ***del);
void				rays_all(t_vars *mlx, t_player *player);
int					parse_one_texture(t_list **head, char **path);
unsigned int		parse_one_colors(t_list **head, char *name, unsigned int *res);
int					parse_window_size(t_vars *v, t_list **head);
t_data				get_picture(void *mlx, char *path);
int					next_line(t_list **head);
void				switch_texture(t_vars *v, char **param, char **path);
int					check_num(char *s);
int					save_bmp(t_vars *v);
void				erase_array_int(int ***del);

#endif