#include "cub3d.h"

int		add_switch_params(t_vars *v, char *param, t_list **head)
{
	unsigned int	tmpint;

	if (param[0] == 'F' && param[1] == ' ')
	{
		if (!(parse_one_colors(head, "F", &tmpint)))
			return (0);
		v->F = tmpint;
		return (1);
	}
	if (param[0] == 'C' && param[1] == ' ')
	{
		if (!(parse_one_colors(head, "C", &tmpint)))
			return (0);
		v->C = tmpint;
		return (1);
	}
	return (-1);
}

int		switch_params(t_vars *v, char *param, t_list **head)
{
	char			*tmp;
	int				tmp_int;
	char			*p;

	if (ft_strncmp(param, "R", 1) == 0 && param[1] == ' ')
		return (parse_window_size(v, head));
	if (((ft_strncmp(param, "NO", 2) == 0 || ft_strncmp(param, "SO", 2) == 0
		|| ft_strncmp(param, "WE", 2) == 0 || ft_strncmp(param, "EA", 2) == 0)
		&& param[2] == ' ') || (ft_strncmp(param, "S ", 2) == 0))
	{
		p = ft_strdup(param);
		if (!parse_one_texture(head, &tmp))
			return (0);
		switch_texture(v, &p, &tmp);
	}
	else if ((tmp_int = add_switch_params(v, param, head)) >= 0)
		return (tmp_int);
	else
		return (errors("Invalid parameter name", NULL));
	return (1);
}

int		parse_lines(t_list **head, t_vars *v)
{
	int		i;
	int		count;

	count = 8;
	while (*head && count > 0)
	{
		i = 0;
		while (*((char *)(*head)->content + i)
			&& *((char *)(*head)->content + i) == ' ')
			i++;
		if (!(*((char *)(*head)->content + i)))
			if (!next_line(head))
				return (errors("Invalid number of parameters)", NULL));
		if (!switch_params(v, (*head)->content + i, head))
			return (0);
		count--;
	}
	if (count == 0)
		return (1);
	return (0);
}

int		parse_file(char *name_of_file, t_vars *v)
{
	int		fd;
	char	*line;
	t_list	*head;

	line = NULL;
	head = NULL;
	fd = open(name_of_file, O_RDONLY);
	if (fd < 0)
		return (errors("File .cub was not found", NULL));
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	if (!parse_lines(&head, v))
		return (0);
	v->cols = 0;
	v->rows = 0;
	if (!parse_map(v, &head))
		return (0);
	return (1);
}
