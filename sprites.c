#include "cub3d.h"


void	draw_sprite(t_vars *v, t_sprite_info *sp_inf, double **buf, int spriteScreenX)
{
	int				temp;
	int				texX;
	int				texY;
	int				d;
	unsigned int	color;

	while (sp_inf->draw_start_x < sp_inf->draw_end_x )
		{
			texX = (int)(256 * (sp_inf->draw_start_x - (-sp_inf->width / 2 +
			spriteScreenX)) * v->s.w / sp_inf->width) / 256;      
			temp = sp_inf->draw_start_y;
			if(sp_inf->transf_y > 0 && v->w - sp_inf->draw_start_x >= 0 &&
			v->w - sp_inf->draw_start_x < v->w && sp_inf->transf_y <
			*(*buf + sp_inf->draw_start_x))
				while(temp < sp_inf->draw_end_y)
				{
					d = (temp) * 256 - v->h * 128 + sp_inf->height * 128;
					texY = ((d * v->s.h) / sp_inf->height) / 256;
					color = my_mlx_pixel_get(&v->s, texX, texY);
					if((color & 0x00FFFFFF) != 0) {
						my_mlx_pixel_put(v->img, v->w - sp_inf->draw_start_x,
						temp, color);
					}
					temp++;
				}
			sp_inf->draw_start_x++;
		}
}

void    sprites(t_vars *v, double **buf)
{
	t_sprite_info sp_inf;

	while(v->sprite)
	{
		sp_inf.x = ((t_sprite *)v->sprite->content)->x + 0.5 - v->player->pos_x;
		sp_inf.y = ((t_sprite *)v->sprite->content)->y + 0.5 - v->player->pos_y;
		double invDet = 1.0 / (v->player->plane_x * v->player->dir_y - v->player->dir_x * v->player->plane_y);
		sp_inf.transf_x = invDet * (v->player->dir_y * sp_inf.x - v->player->dir_x * sp_inf.y);
		sp_inf.transf_y = invDet * (-v->player->plane_y * sp_inf.x + v->player->plane_x * sp_inf.y);
		int spriteScreenX = (int)((v->w / 2) * (1 + sp_inf.transf_x / sp_inf.transf_y));
		sp_inf.height = abs((int)(v->h / (sp_inf.transf_y)));
		sp_inf.draw_start_y = -sp_inf.height / 2 + v->h / 2;
		if(sp_inf.draw_start_y < 0) 
			sp_inf.draw_start_y = 0;
		sp_inf.draw_end_y = sp_inf.height / 2 + v->h / 2;
		if(sp_inf.draw_end_y >= v->h) 
			sp_inf.draw_end_y = v->h - 1;
		sp_inf.width = abs( (int) (v->h / (sp_inf.transf_y)));
		sp_inf.draw_start_x = -sp_inf.width / 2 + spriteScreenX;
		if(sp_inf.draw_start_x < 0) 
			sp_inf.draw_start_x = 0;
		sp_inf.draw_end_x = sp_inf.width / 2 + spriteScreenX;
		if(sp_inf.draw_end_x >= v->w) 
			sp_inf.draw_end_x = v->w - 1;
		draw_sprite(v, &sp_inf, buf, spriteScreenX);
		free(v->sprite->content);
		t_list *tmp;
		tmp = v->sprite;
		v->sprite = v->sprite->next;
		free(tmp);
	}
}

