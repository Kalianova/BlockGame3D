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

void	line_draw(t_data *data, t_data *dst, int x, int height, t_vars *v, int xMap)
{
	double	coef;
	int		horizont;
	int 	i;

	horizont = dst->h / 2 - height / 2;
	coef = (data->h - 1) / (height + 0.0);
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
	{
    if (horizont + height < v->h && horizont + height >= 0)
		  my_mlx_pixel_put(dst, x, horizont + height, my_mlx_pixel_get(data, xMap,(int)(coef * height)));
		height--;
	}

}


/*void  line_draw_sprite(int x, t_vars *v, int beginY, int endY)
{
  double  coef;
  int   i;

  coef = (data->h - 1) / (height + 0.0);
  i = 0;

  while (beginY < endY)
  {
    my_mlx_pixel_put(v->img, x, horizont + height, my_mlx_pixel_get(v->S, xMap,(int)(coef * height)));
    beginY++;
  }
  
 //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
        if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y-vMoveScreen) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * texHeight) / spriteHeight) / 256;
          Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
          if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
}*/

int texX(t_data *image, t_player *player, t_vars *mlx, int side, double perpWallDist)
{
  double wallX; //where exactly the wall was hit
  int texX;

  if (side == 0) 
    wallX = player->posY + perpWallDist * player->rayDirY;
  else           
    wallX = player->posX + perpWallDist * player->rayDirX;
  wallX -= (int)wallX;
  //x coordinate on the texture
  texX = (int)(wallX * (double)(image->w));
  if(side == 0 && player->rayDirX > 0) 
    texX = (image->w) - texX - 1;
  if(side == 1 && player->rayDirY < 0) 
    texX = (image->w) - texX - 1;
  return texX;
}

void putInSprites(t_vars *mlx, int x, int y){
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
  while (now && (((t_sprite *)now->content)->x - mlx->player->posX) * (((t_sprite *)now->content)->x - mlx->player->posX) + 
    (((t_sprite *)now->content)->y - mlx->player->posY) * (((t_sprite *)now->content)->y - mlx->player->posY) 
    > (x - mlx->player->posX) * (x - mlx->player->posX) + (y - mlx->player->posY) * (y - mlx->player->posY))
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

void rayPut(t_vars *mlx, t_player *player, int x){
	//which box of the map we're in
      int mapX = (int)player->posX;
      int mapY = (int)player->posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = (player->rayDirY == 0) ? 0 : ((player->rayDirX == 0) ? 1 : fabs(1 / player->rayDirX));
      double deltaDistY = (player->rayDirX == 0) ? 0 : ((player->rayDirY == 0) ? 1 : fabs(1 / player->rayDirY));
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

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
      if (player->rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (player->posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
      }
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
        if (mlx->map[mapX][mapY] == 2)
        {
          putInSprites(mlx, mapX, mapY);
        }
        if (mlx->map[mapX][mapY] == 1)
          hit = 1;
      } 
      if (side == 0) 
      	perpWallDist = (mapX - player->posX + (1 - stepX) / 2) / player->rayDirX;
      else           
      	perpWallDist = (mapY - player->posY + (1 - stepY) / 2) / player->rayDirY;

       t_data *src;
       //Calculate height of line to draw on screen
      int lineHeight = (int)(mlx->img->h / perpWallDist) ;
      if (side == 0)
      {
        if (player->rayDirX < 0 )
          src = &mlx->WE;
        else
          src = &mlx->NO;
      }
      else
      {
        if (player->rayDirY < 0 )
          src = &mlx->EA;
        else
          src = &mlx->SO;
      }
      if (lineHeight < 0)
        line_draw(src, mlx->img, mlx->img->w - x, -lineHeight, mlx, texX(src, mlx->player, mlx, side, -perpWallDist));
      else
        line_draw(src, mlx->img, mlx->img->w - x, lineHeight, mlx, texX(src, mlx->player, mlx, side, perpWallDist));
 //draw sprites
}


void raysAll(t_vars *mlx, t_player *player){

mlx->sprite = NULL;
	for(int x = 0; x < mlx->img->w; x++)
  {
      //calculate ray position and direction
      double cameraX = 2 * x/(double)mlx->img->w - 1; //x-coordinate in camera space
      player->rayDirX = player->dirX + player->planeX*cameraX;
      player->rayDirY = player->dirY + player->planeY*cameraX;
      rayPut(mlx, player, x);

  }
  sprites(mlx);
  mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}