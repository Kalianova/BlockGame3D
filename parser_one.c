#include "cub3d.h"

void			erase_array(char ***del)
{
	int i;

	i = -1;
	while ((*del)[++i])
		free((*del)[i]);
	free(*del);
}

unsigned int	parse_one_colors(t_list **head, char *name, unsigned int *res)
{
	char			**tmp;
	int				i;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	i = 0;
	if (*head && (tmp = ft_split((*head)->content, ',')) &&
		tmp[0] && tmp[1] && tmp[2] && !tmp[3])
	{
		while (*(tmp[0] + i) == ' ')
			i++;
		if (!next_line(head))
			return (errors("Not enough parameters", &tmp));
		if (ft_strncmp(tmp[0] + i, name, 1) == 0 && ((g = check_num(tmp[1])) < 0
			|| g > 255 || b > 255 || (r = check_num(tmp[0] + i + 1)) < 0
			|| r > 255 || (b = check_num(tmp[2])) < 0))
			return (errors("Invalid number in color rgb", &tmp));
		*res = (r << 16 | g << 8 | b);
		erase_array(&tmp);
		return (1);
	}
	if (!next_line(head))
		return (errors("Not enough parameters", &tmp));
	return (errors("Invalid color parameters", &tmp));
}

int				parse_one_texture(t_list **head, char **path)
{
	char	**tmp;
	int		i;
	int		fd;

	if (*head && (tmp = ft_split((*head)->content, ' ')) &&
		tmp[0] && tmp[1] && !tmp[2])
	{
		*path = ft_strdup(tmp[1]);
		if (!next_line(head))
			return (errors("Not enough parameters", &tmp));
		fd = open(*path, O_RDONLY);
		if (fd < 0)
			return (errors("No texture file", &tmp));
		i = -1;
		while (tmp[++i])
			free(tmp[i]);
		free(tmp);
		return (1);
	}
	return (errors("Invalid texture parameters", &tmp));
}

int				parse_window_size(t_vars *v, t_list **head)
{
	int		i;
	char	**tmp;

	if (*head)
	{
		tmp = ft_split((*head)->content, ' ');
		if (tmp[1] && ft_isdigit(tmp[1][0]) && tmp[2]
			&& ft_isdigit(tmp[2][0]) && !tmp[3])
		{
			if ((v->w = check_num(tmp[1])) < 0
				|| (v->h = check_num(tmp[2])) < 0)
				return (errors("Invalid number in R parameter", &tmp));
		}
		else
			return (errors("Invalid number of parameters in R", &tmp));
		i = -1;
		while (tmp[++i])
			free(tmp[i]);
		free(tmp);
		if (!next_line(head))
			return (errors("Invalid number of parameters)", NULL));
	}
	return (1);
}
