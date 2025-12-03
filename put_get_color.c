#include "header.h"

void put_color(t_data *data, int x, int y, int color)
{
	int *row;

	row = (int *)(data->img_s + y * data->size_line);
	row[x] = color;
}

int get_pixel_color(void *texture_img, int x, int y)
{
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int *pixel;

	addr = mlx_get_data_addr(texture_img, &bits_per_pixel, &line_length, &endian);
	pixel = (int *)(addr + y * line_length);
	return (pixel[x]);
}
