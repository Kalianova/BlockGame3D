#include "cub3d.h"

int errors(char *message, char ***del)
{
	int i;

	i = -1;
	if (del)
	{
		while ((*del)[++i])
			free((*del)[i]);
		free (*del);
	}
	printf("Error!\n%s\n", message);
	fflush(stdout); //Remove it after all
	return (0);
}

int nextLine(t_list **head)
{
	int i;
	t_list *list;


	while (*head)
	{
		list = *head;
		*head = (*head)->next;
		free(list->content);
		free(list);
		if (*head)
		{
			i = 0;
			while (*((char *)(*head)->content + i))
			{
				if (*((char *)(*head)->content + i) != ' ')
					return (1);
				i++;
			}
		}
	}
	return (0);
}

int checkNum(char *s)
{
	int length;
	int num;
	int count;
	int res;

	length = 0;
	s = ft_strtrim(s, " ");
	while (s[length])
		length++;
	num = ft_atoi(s);
	res = num;
	count = 0;
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	if (s[0] == 0)
		count = 1;
	free(s);
	if (count == length)
		return (res);
	return (-1);
}

unsigned int	parseOneColors(t_list **head, char *name, unsigned int *res)
{
	char 	**tmp;
	int		i;
	unsigned char	r;
    unsigned char	g;
    unsigned char	b;

	i = 0;

	if (*head && (tmp = ft_split((*head)->content, ',')) && 
		tmp[0] && tmp[1] && tmp[2] && !tmp[3] )
	{
		while (*(tmp[0] + i) == ' ')
			i++;
		if (!nextLine(head))
			return (errors("Not enough parameters", &tmp));
		if (ft_strncmp(tmp[0] + i, name, 1) == 0)
		if ((r = checkNum(tmp[0] + i + 1) < 0 || r > 255 
			|| (g = checkNum(tmp[1])) < 0 || g > 255 
			|| (b = checkNum(tmp[2])) < 0 || b > 255))
		{
			return (errors("Invalid number in color rgb", &tmp));
		}
		*res = (r << 16 | g << 8 | b);
		i = -1;
		while (tmp[++i])
			free(tmp[i]);
		free (tmp);
		return (1);
	}
	if (!nextLine(head))
		return (errors("Not enough parameters", &tmp));
}

int parseOneTexture(t_list **head, char **path)
{
	char 	**tmp;
	int		i;
	int		fd;

	if (*head && (tmp = ft_split((*head)->content, ' ')) && 
		tmp[0] && tmp[1] && !tmp[2])
	{
		*path = ft_strdup(tmp[1]);
		if (!nextLine(head))
			return (errors("Not enough parameters", &tmp));
		fd = open(*path, O_RDONLY);
		if (fd < 0)
			return (errors("No texture file", &tmp));
		i = -1;
		while (tmp[++i])
			free(tmp[i]);
		free (tmp);
		return (1);
	}
	return (errors("Invalid texture parameters", &tmp));
}


int parseWindowSize(t_vars *v, t_list **head)
{
	int i;
	char **tmp;

	if (*head)
	{
		tmp = ft_split((*head)->content, ' ');
		if (tmp[1] && ft_isdigit(tmp[1][0]) && tmp[2] && ft_isdigit(tmp[2][0]) && !tmp[3])
		{
			if ((v->w = checkNum(tmp[1])) < 0 || (v->h = checkNum(tmp[2])) < 0)
				return (errors("Invalid number in R parameter", &tmp));
		}
		else
			return (errors("Invalid number of parameters in R", &tmp));
		i = -1;
		while (tmp[++i])
			free(tmp[i]);
		free (tmp);
		if(!nextLine(head))
			return (errors("Invalid number of parameters)", NULL));
	}
	return (1);
}

void switchTexture(t_vars *v, char **param, char **path)
{
	if (ft_strncmp(*param, "NO", 2) == 0)
		v->NO = *path;
	if (ft_strncmp(*param, "EA", 2) == 0)
		v->EA = *path;
	if (ft_strncmp(*param, "SO", 2) == 0)
		v->SO = *path;
	if (ft_strncmp(*param, "WE", 2) == 0)
		v->WE = *path;
	if (ft_strncmp(*param, "S", 1) == 0)
		v->S = *path;
	free(*param);
}


int switchParams(t_vars *v, char *param, t_list **head)
{
	char	*tmp;
	unsigned int 	*tmpint;
	char	*p;

	if (ft_strncmp(param, "R", 1) == 0 && param[1] == ' ')
		return (parseWindowSize(v, head));
	if (((ft_strncmp(param, "NO", 2) == 0 || ft_strncmp(param, "SO", 2) == 0 
		|| ft_strncmp(param, "WE", 2) == 0 || ft_strncmp(param, "EA", 2) == 0)
		&& param[2] == ' ') || (ft_strncmp(param, "S ", 2) == 0))
	{
		p = ft_strdup(param);
		if (!parseOneTexture(head, &tmp))
			return (0);
		switchTexture(v, &p, &tmp);
	}
	else if (ft_strncmp(param, "F", 1) == 0 && param[1] == ' ')
	{
		if (!(parseOneColors(head,"F", &tmpint)))
			return (0);
		v->F = tmpint;
	}	
	else if (ft_strncmp(param, "C", 1) == 0 && param[1] == ' ')
	{
		if (!(parseOneColors(head,"C", &tmpint)))
			return (0);
		v->C = tmpint;
	}
	else{
		return (errors("Invalid parameter name", NULL));
	}
	return (1);
}

int parseLines(t_list **head, t_vars *v)
{
	int i;
	char **tmp;
	int count;

	count = 8;
	while (*head && count > 0)
	{
		i = 0;
		while (*((char *)(*head)->content + i) 
			&& *((char *)(*head)->content + i) == ' ')
			i++;
		if (!(*((char *)(*head)->content + i)))
			if(!nextLine(head))
				return (errors("Invalid number of parameters)", NULL));
		if (!switchParams(v, (*head)->content + i, head))
			return (0);
		count--;
	}
	if (count == 0)
		return (1);
	return (0);
}

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
			v->player->posY = i;
			v->player->posX = j;
			//DIractions of player
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

int	parseFile(char *name_of_file, t_vars *v)
{
	int	fd;
	char	  *line = NULL;
	t_list	*head = NULL;

	fd = open(name_of_file, O_RDONLY);
	if (fd < 0)
		return (errors("File .cub was not found", NULL));
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	if (!parseLines(&head, v))
		return (0);
	if (!parseMap(v, &head))
		return (0);
	return (1);
}