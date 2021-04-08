/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 18:51:58 by astaryu           #+#    #+#             */
/*   Updated: 2021/04/02 18:52:00 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*put_in_sprites_add(t_vars *mlx, int x, int y, t_list **now)
{
	t_list		*last;

	last = NULL;
	while (*now && (((t_sprite *)(*now)->content)->x - mlx->player->pos_x) *
	(((t_sprite *)(*now)->content)->x - mlx->player->pos_x) +
	(((t_sprite *)(*now)->content)->y - mlx->player->pos_y) *
	(((t_sprite *)(*now)->content)->y - mlx->player->pos_y)
	> (x - mlx->player->pos_x) * (x - mlx->player->pos_x) +
	(y - mlx->player->pos_y) * (y - mlx->player->pos_y))
	{
		last = *now;
		*now = (*now)->next;
	}
	return (last);
}

void	put_in_sprites_choose(t_vars *mlx, t_list **now,
t_list **last, t_sprite **sp)
{
	if (*now == NULL)
	{
		*now = ft_lstnew(*sp);
		(*last)->next = *now;
		return ;
	}
	if (*last == NULL)
	{
		mlx->sprite = ft_lstnew(*sp);
		mlx->sprite->next = *now;
		return ;
	}
	(*last)->next = ft_lstnew(*sp);
	(*last)->next->next = *now;
}

void	put_in_sprites(t_vars *mlx, int x, int y)
{
	t_list		*now;
	t_list		*last;
	t_sprite	*sp;

	now = mlx->sprite;
	sp = (t_sprite *)malloc(sizeof(t_sprite));
	if (!sp)
		return ;
	sp->x = x;
	sp->y = y;
	if (now == NULL)
	{
		mlx->sprite = ft_lstnew(sp);
		return ;
	}
	last = put_in_sprites_add(mlx, x, y, &now);
	if (now && ((t_sprite *)now->content)->x == x &&
	((t_sprite *)now->content)->y == y)
	{
		free(sp);
		return ;
	}
	put_in_sprites_choose(mlx, &now, &last, &sp);
}

void	rays_all(t_vars *mlx, t_player *player, int bmp)
{
	int		x;
	double	camera_x;
	double	*buf;

	x = -1;
	mlx->sprite = NULL;
	if (!(buf = (double *)malloc(sizeof(double) * mlx->img->w)))
		return ;
	while (++x < mlx->img->w)
	{
		camera_x = 2 * x / (double)mlx->img->w - 1;
		player->r_dir_x = player->dir_x + player->plane_x * camera_x;
		player->r_dir_y = player->dir_y + player->plane_y * camera_x;
		ray_put(mlx, x, &buf);
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
