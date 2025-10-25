#include "header.h"

void put_color(t_data *data, int x, int y, int color)
{
	int *row;

	row = (int *)(data->img_s + y * data->size_line);
	row[x] = color;
}

void    draw_line(t_data *data,int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        put_color(data, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_rectangle(t_data *data, int x, int y, int tile_size,int color)
{
	int i;
	int j;

	i = y;
	while (i < y + tile_size)
	{
		j = x;
		while (j < x + tile_size)
		{
			put_color(data, j, i, color);
			j++;
		}
		i++;
	}
	
}
