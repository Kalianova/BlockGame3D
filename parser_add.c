/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:47:07 by astaryu           #+#    #+#             */
/*   Updated: 2021/03/26 14:47:10 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		errors(char *message, char ***del)
{
	int i;

	i = -1;
	if (del)
	{
		while ((*del)[++i])
			free((*del)[i]);
		free(*del);
	}
	printf("Error!\n%s\n", message);
	return (0);
}

int		check_num(char *s)
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
	if (s[0] == '0')
		count = 1;
	free(s);
	if (count == length)
		return (res);
	return (-1);
}

int		next_line(t_list **head)
{
	int		i;
	t_list	*list;

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

int		switch_texture(t_vars *v, char **param, char **path)
{
	t_data	pic;
	int		res;
	
	res = get_picture(v->mlx, *path, &pic);
	if (ft_strncmp(*param, "NO", 2) == 0)
		v->no = pic;
	if (ft_strncmp(*param, "EA", 2) == 0)
		v->ea = pic;
	if (ft_strncmp(*param, "SO", 2) == 0)
		v->so = pic;
	if (ft_strncmp(*param, "WE", 2) == 0)
		v->we = pic;
	if (ft_strncmp(*param, "S", 1) == 0)
		v->s = pic;
	free(*param);
	free(*path);
	if (res == 0)
		return (errors("Invalide texture picture", NULL));
	return (1);
}

int		get_picture(void *mlx, char *path, t_data *pic)
{
	t_data img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.w, &img.h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
		&img.endian);
	if (!img.img || !img.addr)
		return (0);
	*pic = img;
	return (1);
}
