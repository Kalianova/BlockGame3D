#include "cub3d.h"

void	add_int(unsigned char *header, int num)
{
	header[0] = (unsigned char)num;
	header[1] = (unsigned char)(num >> 8);
	header[2] = (unsigned char)(num >> 16);
	header[3] = (unsigned char)(num >> 24);
}

void header_bmp(t_vars *v, int file_fd)
{
	unsigned char	header[54];
	int 			i;

	i = 0;
	while (++i < 54)
		header[i] = 0;
	header[0] = 'B';
	header[1] = 'M';
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	header[27] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	add_int(header + 2, (int)(54 + 3 * v->w * v->h));
	add_int(header + 18, v->w);
	add_int(header + 22, v->h);
	write(file_fd, header, 54);
}

int put_image(t_vars *v, int fileFd)
{
	int i;
	int j;
	int color;

	i = -1;
	while (++i < v->h)
	{
		j = -1;
		while (++j < v->w)
		{
			color = my_mlx_pixel_get(v->img, i, j);
			if(write(fileFd, &color, 3) < 0)
				return 0;
		}
	}
	return (1);
}

int save_bmp(t_vars *v)
{
	int file_fd;

	if ((file_fd = open("cub3d.bmp"
		, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND)) <= 0)
		return (0);
	header_bmp(v, file_fd);
	put_image(v, file_fd);
	close(file_fd);
	return (1);
}