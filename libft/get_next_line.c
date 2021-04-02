/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaryu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:05:36 by astaryu           #+#    #+#             */
/*   Updated: 2020/10/28 21:06:53 by astaryu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*substr_del(char *s, unsigned int start, size_t len)
{
	char *tmp;

	tmp = ft_substr(s, start, len);
	free(s);
	return (tmp);
}

static char	*strjoin_del(char *s1, char const *s2)
{
	char *tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

static int	remain_data(int fd, char **line, char **data)
{
	int		size;
	char	*n_point;

	if ((n_point = ft_strchr(data[fd], '\n')))
	{
		*line = substr_del(ft_strdup(data[fd]), 0, n_point - data[fd]);
		size = n_point - data[fd] + 1;
		data[fd] = substr_del(data[fd], size, ft_strlen(data[fd]) - size);
		return (1);
	}
	*line = ft_strdup(data[fd]);
	free(data[fd]);
	data[fd] = NULL;
	return (0);
}

static int	line_read(int fd, char **line, char **data)
{
	int		size;
	char	buffer[BUFFER_SIZE + 1];
	char	*n_point;
	char	*tmp;

	while ((size = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[size] = '\0';
		if ((n_point = ft_strchr(buffer, '\n')))
		{
			tmp = substr_del(ft_strdup(buffer), 0, n_point - buffer);
			*line = strjoin_del(*line, tmp);
			free(tmp);
			data[fd] = ft_strdup(n_point + 1);
			return (1);
		}
		*line = strjoin_del(*line, buffer);
	}
	return (size);
}

int			get_next_line(int fd, char **line)
{
	static char *data[SIZE_OF_FD];

	if (fd < 0 || (line == NULL && data[fd] == NULL))
		return (-1);
	if (data[fd] != NULL)
	{
		if (remain_data(fd, line, data))
			return (1);
	}
	else
	{
		if (!(*line = (char*)malloc((1) * sizeof(char))))
			return (-1);
		*line[0] = '\0';
	}
	return (line_read(fd, line, data));
}
