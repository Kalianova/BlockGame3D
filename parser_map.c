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
	v->player->dirX = dx;
	v->player->dirY = dy;
	v->player->planeX = 0;
	v->player->planeY = 0;
	return (v->w / (v->h + 0.0) / 2);
}

int		make_player(t_vars *v, char c, int i, int j)
{
	v->player->moveSpeed = 0.07;
	v->player->rotSpeed = 0.1;
	if (v->player->posX >= 0.0)
		return (errors("Multiple players", NULL));
	v->player->posY = j + 0.5;
	v->player->posX = i + 0.5;
	if (c == 'N')
		v->player->planeX = -1 * init_player(v, 0, 1);
	if (c == 'S')
		v->player->planeX = init_player(v, 0, -1);
	if (c == 'W')
		v->player->planeY = -1 * init_player(v, -1, 0);
	if (c == 'E')
		v->player->planeY = init_player(v, 1, 0);
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

int		parse_map(t_vars *v, t_list **head)
{
	t_list	*tmp;
	int		i;

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
	i = 0;
	while (i < v->rows)
	{
		v->map[i] = (int *)malloc(sizeof(int) * v->cols);
		if (!convert_map(v, i, head))
			return (0);
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
		i++;
	}
	return (validate_map(v, v->rows, v->cols));
}
