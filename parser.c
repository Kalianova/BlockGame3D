/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 18:56:04 by astaryu           #+#    #+#             */
/*   Updated: 2021/04/02 18:56:06 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		add_switch_params(t_vars *v, char *param, t_list **head)
{
	unsigned int	tmpint;

	if (param[0] == 'F' && param[1] == ' ')
	{
		if (v->f == 4294967294)
		{
			if (!(parse_one_colors(head, "F", &tmpint)))
				return (0);
			v->f = tmpint;
			return (1);
		}
		return (errors("Multiple color params", NULL));
	}
	if (param[0] == 'C' && param[1] == ' ')
	{
		if (v->c == 4294967294)
		{
			if (!(parse_one_colors(head, "C", &tmpint)))
				return (0);
			v->c = tmpint;
			return (1);
		}
		return (errors("Multiple color params", NULL));
	}
	return (-1);
}

int		switch_params(t_vars *v, char *param, t_list **head)
{
	char			*tmp;
	int				tmp_int;
	char			*p;

	if (ft_strncmp(param, "R", 1) == 0 && param[1] == ' ')
	{
		if (v->w < 0 && v->h < 0)
			return (parse_window_size(v, head));
		return (errors("Multiple R parameter", NULL));
	}
	if (((ft_strncmp(param, "NO", 2) == 0 || ft_strncmp(param, "SO", 2) == 0
		|| ft_strncmp(param, "WE", 2) == 0 || ft_strncmp(param, "EA", 2) == 0)
		&& param[2] == ' ') || (ft_strncmp(param, "S ", 2) == 0))
	{
		p = ft_strdup(param);
		if (!parse_one_texture(head, &tmp) || !switch_texture(v, &p, &tmp))
			return (0);
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
	if (ft_strncmp(name_of_file - 4 + ft_strlen(name_of_file), ".cub", 5))
		exit(errors("File format is not .cub", NULL));
	fd = open(name_of_file, O_RDONLY);
	if (fd < 0)
		exit(errors("File .cub was not found", NULL));
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	if (!parse_lines(&head, v))
	{
		close(fd);
		return (0);
	}
	v->cols = 0;
	v->rows = 0;
	close(fd);
	if (!parse_map(v, &head, -1))
		return (0);
	return (1);
}
