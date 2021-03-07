#include "cub3d.h"

int validateMap(t_vars *v, int rows, int cols)
{
	int i;
	int j;
	
	i = -1;
	j = -1;
	while (++i < cols)
		if (v->map[0][i] == 0 || v->map[0][i] == 2 
			|| v->map[rows - 1][i] == 0 || v->map[rows-1][i] == 2)
			return (errors("Invalid map, not closed", NULL));

	while (++j < rows)
		if (v->map[j][0] == 0 || v->map[j][0] == 0 
			|| v->map[j][cols - 1] == 0 || v->map[j][cols - 1] == 2)
			return (errors("Invalid map, not closed", NULL));
	j = 0;
	i = 0;
	while (++i < rows - 1 + (j = 0))
		while (++j < cols - 1)
			if ((v->map[i][j] == 0 || v->map[i][j] == 2) 
				&& (v->map[i - 1][j] == -1 || v->map[i + 1][j] == -1
				|| v->map[i][j - 1] == -1 || v->map[i][j + 1] == -1 ))
				return (errors("Invalid map, not closed", NULL));
	j = 0;
	i = 0;
	while (i++ < rows + (j = 0))
		while (j++ < cols)
			if (v->map[i - 1][j - 1] == -1)
				v->map[i - 1][j - 1] = 1;
	return (1);
}

int makePlayer(t_vars *v, char c, int i, int j)
{
	v->player->moveSpeed = 0.07;
	v->player->rotSpeed = 0.1;
	if (v->player->posX >= 0.0)
		return (errors("Multiple players", NULL));
	v->player->posY = j + 0.5;
	v->player->posX = i + 0.5;
	if (c == 'N'){
		v->player->dirX = 0;
		v->player->dirY = 1;
		v->player->planeX = -1 * v->w / (v->h + 0.0) / 2;
		v->player->planeY = 0;
	}
	if (c == 'S'){
		v->player->dirX = 0;
		v->player->dirY = -1;
		v->player->planeX = 1 * v->w / (v->h + 0.0) / 2;
		v->player->planeY = 0;
	}
	if (c == 'W'){
		v->player->dirX = -1;
		v->player->dirY = 0;
		v->player->planeX = 0;
		v->player->planeY = -1 * v->w / (v->h + 0.0) / 2;
	}
	if (c == 'E'){
		v->player->dirX = 1;
		v->player->dirY = 0;
		v->player->planeX = 0;
		v->player->planeY = 1 * v->w / (v->h + 0.0) / 2;
	}
	return (1);
}

int convertMap(t_vars *v, int i, t_list **head)
{
	int j;

	j = 0;
	while (j < v->cols && ((char *)(*head)->content)[j])
	{
		if (((char *)(*head)->content)[j] == '0')
			v->map[i][j] = 0;
		else if (((char *)(*head)->content)[j] == '1')
			v->map[i][j] = 1;
		else if (((char *)(*head)->content)[j] == '2')
			v->map[i][j] = 2;
		else if (((char *)(*head)->content)[j] == ' '){
			v->map[i][j] = -1;		
		}
		else if (((char*)(*head)->content)[j] == 'N' || ((char *)(*head)->content)[j] == 'S'
			|| ((char *)(*head)->content)[j] == 'E' || ((char *)(*head)->content)[j] == 'W')
		{
			v->map[i][j] = 0;
			if(!makePlayer(v, ((char*)(*head)->content)[j], i, j))
				return (0);
		}
		else
			return (errors("Invalid charachter in map", NULL));
		j++;
	}
	while (j++ <= v->cols)
		v->map[i][j - 1] = -1;
	return (1);
}

int parseMap(t_vars *v, t_list **head)
{
	t_list *tmp;
	int count;
	int maxLength;
	int i;

	tmp = *head;
	maxLength = 0;
	count = 0;
	while (tmp)
	{
		if (ft_strlen(tmp->content) > maxLength)
			maxLength = ft_strlen(tmp->content);
		tmp = tmp->next;
		count++;
	}
	v->map = (int **)malloc(sizeof(int *) * (count));
	v->rows = count;
	v->cols = maxLength;
	i = 0;
	while (i < count)
	{
		v->map[i] = (int *)malloc(sizeof(int) * maxLength);
		if (!convertMap(v, i, head))
			return (0);
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
		i++;
	}
	return (validateMap(v, v->rows, v->cols));
}