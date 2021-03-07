#include "cub3d.h"

void    sprites(t_vars *v, double **buf)
{
	while(v->sprite)
	{
		//translate sprite position to relative to camera
		double spriteX = ((t_sprite *)v->sprite->content)->x + 0.5 - v->player->posX;
		double spriteY = ((t_sprite *)v->sprite->content)->y + 0.5 - v->player->posY;
	//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]
		double invDet = 1.0 / (v->player->planeX * v->player->dirY - v->player->dirX * v->player->planeY); //required for correct matrix multiplication
		double transformX = invDet * (v->player->dirY * spriteX - v->player->dirX * spriteY);
		double transformY = invDet * (-v->player->planeY * spriteX + v->player->planeX * spriteY);
		 //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])
		int spriteScreenX = (int)((v->w / 2) * (1 + transformX / transformY)); //was w
		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(v->h / (transformY))); //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + v->h / 2;
		if(drawStartY < 0) 
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + v->h / 2;
		if(drawEndY >= v->h) 
			drawEndY = v->h - 1;
			//calculate width of the sprite
		int spriteWidth = abs( (int) (v->h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) 
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= v->w) 
			drawEndX = v->w - 1;

		int temp;
		while (drawStartX < drawEndX + 1)
		{
			int texX = (int)(256 * (drawStartX - (-spriteWidth / 2 + spriteScreenX)) * v->S.w / spriteWidth) / 256;      
			temp = drawStartY;
			if(transformY > 0 && v->w - drawStartX >= 0 && v->w - drawStartX < v->w && transformY < *(*buf + drawStartX))
				while(temp < drawEndY) //for every pixel of the current stripe
				{
					int d = (temp) * 256 - v->h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * v->S.h) / spriteHeight) / 256;
					unsigned int color = my_mlx_pixel_get(&v->S, texX, texY); //get current color from the texture
					if((color & 0x00FFFFFF) != 0) {
						my_mlx_pixel_put(v->img, v->w - drawStartX, temp, color);
					}
					temp++;
				}
			drawStartX++;
		}
		free(v->sprite->content);
		t_list *tmp;
		tmp = v->sprite;
		v->sprite = v->sprite->next;
		free(tmp);
	}
}

