/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:30:58 by astaryu           #+#    #+#             */
/*   Updated: 2021/03/26 15:31:01 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		validate_map(t_vars *v, int rows, int cols)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < cols)
		if (v->map[0][i] == 0 || v->map[0][i] == 2
			|| v->map[rows - 1][i] == 0 || v->map[rows - 1][i] == 2)
			return (errors("Invalid map, not closed", NULL));
	while (++j < rows + (i = 0))
		if (v->map[j][0] == 0 || v->map[j][0] == 0
			|| v->map[j][cols - 1] == 0 || v->map[j][cols - 1] == 2)
			return (errors("Invalid map, not closed", NULL));
	while (++i < rows - 1 + (j = 0))
		while (++j < cols - 1)
			if ((v->map[i][j] == 0 || v->map[i][j] == 2)
				&& (v->map[i - 1][j] == -1 || v->map[i + 1][j] == -1
				|| v->map[i][j - 1] == -1 || v->map[i][j + 1] == -1))
				return (errors("Invalid map, not closed", NULL));
	i = 0;
	while (i++ < rows + (j = 0))
		while (j++ < cols)
			if (v->map[i - 1][j - 1] == -1)
				v->map[i - 1][j - 1] = 1;
	return (1);
}

double	init_player(t_vars *v, int dx, int dy)
{
	v->player->dir_x = dx;
	v->player->dir_y = dy;
	v->player->plane_x = 0;
	v->player->plane_y = 0;
	return (v->w / (v->h + 0.0) / 2);
}

int		make_player(t_vars *v, char c, int i, int j)
{
	v->player->move_speed = 0.07;
	v->player->rot_speed = 0.1;
	if (v->player->pos_x >= 0.0)
		return (errors("Multiple players", NULL));
	v->player->pos_y = j + 0.5;
	v->player->pos_x = i + 0.5;
	if (c == 'N')
		v->player->plane_x = -1 * init_player(v, 0, 1);
	if (c == 'S')
		v->player->plane_x = init_player(v, 0, -1);
	if (c == 'W')
		v->player->plane_y = -1 * init_player(v, -1, 0);
	if (c == 'E')
		v->player->plane_y = init_player(v, 1, 0);
	return (1);
}

int		convert_map(t_vars *v, int i, t_list **head)
{
	int		j;
	char	c;

	j = -1;
	while (++j < v->cols && (c = ((char *)(*head)->content)[j]))
		if (((char *)(*head)->content)[j] == '0')
			v->map[i][j] = 0;
		else if (c == '1')
			v->map[i][j] = 1;
		else if (c == '2')
			v->map[i][j] = 2;
		else if (c == ' ')
			v->map[i][j] = -1;
		else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			v->map[i][j] = 0;
			if (!make_player(v, c, i, j))
				return (0);
		}
		else
			return (errors("Invalid charachter in map", NULL));
	while (j++ <= v->cols)
		v->map[i][j - 1] = -1;
	return (1);
}

int		parse_map(t_vars *v, t_list **head, int i)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->content) > v->cols)
			v->cols = ft_strlen(tmp->content);
		tmp = tmp->next;
		v->rows++;
	}
	v->map = (int **)malloc(sizeof(int *) * (v->rows + 1));
	v->map[v->rows] = NULL;
	while (++i < v->rows)
	{
		v->map[i] = (int *)malloc(sizeof(int) * v->cols);
		if (!convert_map(v, i, head))
			return (0);
		tmp = *head;
		*head = (*head)->next;
		ft_lstdelone(tmp, (free));
	}
	if (v->player->pos_x < 0.0)
		return (errors("No player", NULL));
	return (validate_map(v, v->rows, v->cols));
}
