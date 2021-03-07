#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <math.h>
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "fcntl.h"

#define KEY_ESC 53
#define KEY_W 119 //13 //119
#define KEY_A 97 // 0 //97
#define KEY_S 115 //1 //115
#define KEY_D 100 //2 //100
#define KEY_ARROW_LEFT 65361 //123 //65361
#define KEY_ARROW_RIGHT 65363 //124 //65363

#define SCALE 16

typedef struct 	s_sprite
{
	int			x;
	int			y;
}				t_sprite;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int			w;
    int			h;
}               t_data;

typedef struct  s_player {
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		rayDirX;
	double		rayDirY;
	double 		planeX;
	double		planeY;
	double		moveSpeed;
	double		rotSpeed;
}				t_player;

typedef struct  s_vars {
    void        *mlx;
    void        *win;
    int			w;
    int			h;
    t_data		*img;
    t_data		WE;
	t_data		EA;
	t_data		NO;
	t_data		SO;
	t_data 		S;
	unsigned int	F;
	unsigned int	C;
	t_list		*sprite;
	int 		rows;
	int			cols;
    int			**map;
    t_player	*player;
}               t_vars;
	


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int 	my_mlx_pixel_get(t_data *data, int x, int y);
//void	line_draw(t_data *data, t_data *dst, int x, int height, t_vars *v);
int		parseFile(char *name_of_file, t_vars *v);
int		key_hook(int keycode, t_vars *vars);
void    sprites(t_vars *v);

void	raysAll(t_vars *mlx, t_player *player);

#endif