#include "cub3d.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

int             key_hook(int keycode, t_vars *vars)
{
	printf("%d\n", keycode);
	if (keycode == KEY_ESC)
	{
    	mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
		exit(0);
	}
	else
		write(1, "s", 1);
	return (0);
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	int     img_w;
    int     img_h;
	char *path_1 = "pictures/red_brick.xpm";

	int x = 40;
	int y = 40;

	img_w = 1;
    img_h = 1;
	int i[5];


	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Cub3d");
	void *mlx_image = mlx_new_image(mlx, 1920, 1080);
	img = mlx_xpm_file_to_image(mlx, path_1, &img_w, &img_h);
	if (img == NULL)
		write(1, "f", 1);
	char *data = mlx_get_data_addr(img, &(i[0]), &(i[1]), &(i[2]));
	while (y++ < 200)
	{
		x = 40;
		while(x++ < 200)
		{
			unsigned int color = mlx_get_color_value(mlx, (int)data[x*img_w + y]);
			mlx_pixel_put(mlx, mlx_win, x, y, color);
		}
	}
write(1, "s", 1);
	t_vars      vars;
	vars.mlx = mlx;
	vars.win = mlx_win;
	mlx_key_hook(vars.win, key_hook, &vars);

	mlx_put_image_to_window(mlx, mlx_win, mlx_image, 0, 0);
	mlx_loop(mlx);
}