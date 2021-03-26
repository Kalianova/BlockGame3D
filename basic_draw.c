#include "cub3d.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int     my_mlx_pixel_get(t_data *data, int x, int y)
{
	char            *dst;
	unsigned char   r;
	unsigned char   g;
	unsigned char   b;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	b = dst[0];
	g = dst[1];
	r = dst[2];
	return (r << 16 | g << 8 | b);
}

void    line_draw(t_data *data, t_data *dst, int x, long long int height, t_vars *v, int xMap)
{
	double  coef;
	long long int       horizont;
	int     i;


	horizont = dst->h / 2 - height / 2;
	if (horizont < -1000000)
	return ;
	coef = (data->h - 1) / (height + 0.0);
	i = 0;
	while (i < horizont)
	{  
		my_mlx_pixel_put(dst, x, i, v->c);
		i++;
	}
	i = horizont + height;
	while (i < dst->h)
	{
		my_mlx_pixel_put(dst, x, i, v->f);
		i++;
	}
	while (height > 0)
	{
		if (horizont + height < v->h && horizont + height >= 0)
			my_mlx_pixel_put(dst, x, horizont + height, my_mlx_pixel_get(data, xMap,(int)(coef * height)));
		height--;
	}
	printf("%i\n", xMap);
	fflush(stdout);
}

int tex_x(t_data *image, t_player *player, int side, double wall_dist)
{
	double wallX;
	int tex_x;

	if (side == 0) 
		wallX = player->pos_y + wall_dist * player->r_dir_y;
	else           
		wallX = player->pos_x + wall_dist * player->r_dir_x;
	wallX -= (int)wallX;
	tex_x = (int)(wallX * (double)(image->w));
	if(side == 0 && player->r_dir_x > 0) 
		tex_x = (image->w) - tex_x - 1;
	if(side == 1 && player->r_dir_y < 0) 
		tex_x = (image->w) - tex_x - 1;
	return tex_x;
}

void	putInSprites(t_vars *mlx, int x, int y){
	t_list *now;
	t_list *last;
	t_sprite *sp;

	now = mlx->sprite;
	last = NULL;
	sp = (t_sprite *)malloc(sizeof(t_sprite));
	sp->x = x;
	sp->y = y;
	if (now == NULL)
	{
		mlx->sprite = ft_lstnew(sp);
		return;
	}
	while (now && (((t_sprite *)now->content)->x - mlx->player->pos_x) * (((t_sprite *)now->content)->x - mlx->player->pos_x) + 
	(((t_sprite *)now->content)->y - mlx->player->pos_y) * (((t_sprite *)now->content)->y - mlx->player->pos_y) 
	> (x - mlx->player->pos_x) * (x - mlx->player->pos_x) + (y - mlx->player->pos_y) * (y - mlx->player->pos_y))
	{
		last = now;
		now = now->next;
	}
	if (now && ((t_sprite *)now->content)->x == x && ((t_sprite *)now->content)->y == y)
	{  
		free(sp);
		return;
	}
	if (now == NULL)
	{
		now = ft_lstnew(sp);
		last->next = now;
		return ;
	}
	if (last == NULL)
	{
		mlx->sprite = ft_lstnew(sp);
		mlx->sprite->next = now;
		return ;
	}
	last->next = ft_lstnew(sp);
	last->next->next = now;
}

t_data	*choose_side(t_vars *mlx, t_player *player, int side)
{
	t_data *src;
	
	if (side == 0)
	{
		if (player->r_dir_x < 0)
			src = &mlx->we;
		else
			src = &mlx->no;
	}
	else
	{
		if (player->r_dir_y < 0)
			src = &mlx->ea;
		else
			src = &mlx->so;
	}
	return (src);
}

void	rayPut(t_vars *mlx, t_player *player, int x, double **buf)
{
	double dist_x;
	double dist_y;
	double wall_dist;
	int step_x;
	int step_y;
	int side;
	long long int line_h;

	int map_x = (int)player->pos_x;
	int map_y = (int)player->pos_y;
	double deltaDistX = (player->r_dir_y == 0) ? 0 : ((player->r_dir_x == 0) ? 1 : fabs(1 / player->r_dir_x));
	double deltaDistY = (player->r_dir_x == 0) ? 0 : ((player->r_dir_y == 0) ? 1 : fabs(1 / player->r_dir_y));
	if (player->r_dir_x < 0)
	{
		step_x = -1;
		dist_x = (player->pos_x - map_x) * deltaDistX;
	}
	else
	{
		step_x = 1;
		dist_x = (map_x + 1.0 - player->pos_x) * deltaDistX;
	}
	if (player->r_dir_y < 0)
	{
		step_y = -1;
		dist_y = (player->pos_y - map_y) * deltaDistY;
	}
	else
	{
		step_y = 1;
		dist_y = (map_y + 1.0 - player->pos_y) * deltaDistY;
	}
	while (mlx->map[map_x][map_y] != 1)
	{
		if (dist_x < dist_y)
		{
			dist_x += deltaDistX;
			map_x += step_x;
			side = 0;
		}
		else
		{
			dist_y += deltaDistY;
			map_y += step_y;
			side = 1;
		}
		if (mlx->map[map_x][map_y] == 2)
			putInSprites(mlx, map_x, map_y);
	} 
	if (side == 0) 
		wall_dist = (map_x - player->pos_x + (1 - step_x) / 2) / player->r_dir_x;
	else           
		wall_dist = (map_y - player->pos_y + (1 - step_y) / 2) / player->r_dir_y;
	line_h = llabs((int)(mlx->img->h / wall_dist)) ;
	line_draw(choose_side(mlx, player, side), mlx->img, mlx->img->w - x, line_h, mlx, tex_x(choose_side(mlx, player, side), player, side, fabs(wall_dist)));
	((*buf)[x]) = wall_dist;
}


void rays_all(t_vars *mlx, t_player *player, int bmp)
{
	mlx->sprite = NULL;
	double *buf = (double *)malloc(sizeof(double) * mlx->img->w);
	for(int x = 1; x < mlx->img->w; x++)
	{
		double cameraX = 2 * x/(double)mlx->img->w - 1;
		player->r_dir_x = player->dir_x + player->plane_x*cameraX;
		player->r_dir_y = player->dir_y + player->plane_y*cameraX;
		rayPut(mlx, player, x, &buf);
	}
	sprites(mlx, &buf);
	free(buf);
	if (bmp)
	{
		save_bmp(mlx);
		delete_all(mlx);
    	key_close(1, mlx);
	}
	else
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}