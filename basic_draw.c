#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int 	my_mlx_pixel_get(t_data *data, int x, int y)
{
    char    		*dst;
    unsigned char	r;
    unsigned char	g;
    unsigned char	b;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    b = dst[0];
    g = dst[1];
    r = dst[2];
    return (r << 16 | g << 8 | b);
}

void	line_draw(t_data *data, t_data *dst, int x, int height, t_vars *v)
{
	double	coef;
	int		horizont;
	int 	i;

	horizont = dst->h / 2 - height / 2;
	coef = data->h / (height + 0.0);
	i = 0;
	while (i <= horizont)
	{
		my_mlx_pixel_put(dst, x, i, v->C);
		i++;
	}
	i = horizont + height;
	while (i <= dst->h)
	{
		my_mlx_pixel_put(dst, x, i, v->F);
		i++;
	}
	while (height > 0)
	{//check edges
		my_mlx_pixel_put(dst, x, horizont + height, my_mlx_pixel_get(data, x,(int)(coef * height) - 1));
		height--;
	}

}

/*void	square_draw(t_data *data, t_data *dst, int x, int dist, int angle)
{
	int side = 0;
	double mapX = 3;
	double posX = 2;
	double stepX = 0.3;
	double rayDirX = 0.7;
	double perpWallDist ;

	for (int i = 0;)

	if (side == 0) 
		perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
    //else           
     	//perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
	for(int i = 1; i < 10; i++){
		rayDirX = i / 10.0;
		perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		int lineHeight = (int)(h / perpWallDist);
		//line_draw(i, lineHeight);
	}
}*/


void rayPut(t_vars *mlx, t_player *player, int x){
	//which box of the map we're in
      int mapX = (int)player->posX;
      int mapY = (int)player->posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = (player->rayDirY == 0) ? 0 : ((player->rayDirX == 0) ? 1 : abs(1 / player->rayDirX));
      double deltaDistY = (player->rayDirX == 0) ? 0 : ((player->rayDirY == 0) ? 1 : abs(1 / player->rayDirY));
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if (player->rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (player->posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - player->posX) * deltaDistX;
      }
      if (player->dirY < 0)
      {
        stepY = -1;
        sideDistY = (player->posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
      }
printf("%f %f\n", player->rayDirX, player->rayDirY);
fflush(stdout);

      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (mlx->map[mapX][mapY] > 0) hit = 1;
      } 
      if (side == 0) 
      	perpWallDist = (mapX - player->posX + (1 - stepX) / 2) / player->rayDirX;
      else           
      	perpWallDist = (mapY - player->posY + (1 - stepY) / 2) / player->rayDirY;
       //Calculate height of line to draw on screen
      int lineHeight = (int)(mlx->img->h / perpWallDist);
      if (lineHeight / 2 + mlx->img->h / 2)
      	lineHeight = mlx->img->h;
      //line_draw(mlx->WE.img, mlx->img, x, lineHeight, mlx);

printf("%f %f %f %f\n", stepX, stepY, lineHeight, perpWallDist);
fflush(stdout);
}


void raysAll(t_vars *mlx, t_player *player){

	for(int x = 0; x < mlx->img->w; x++)
    {

      //calculate ray position and direction
      double cameraX = 2*x/(double)mlx->img->w-1; //x-coordinate in camera space
      player->rayDirX = player->dirX + player->planeX*cameraX;
      player->rayDirY = player->dirY + player->planeY*cameraX;

      rayPut(mlx, player, x);

  }
  mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}