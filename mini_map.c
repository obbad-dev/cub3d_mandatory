#include "header.h"

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		put_color(data, x0, y0, color);
		
		if (x0 == x1 && y0 == y1)
			break;
		
		e2 = 2 * err;
		
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

void cast_rays(t_data *data, t_cast *cast)
{

	int i;

	i = 0;
	while(i < NUM_RAYS)
	{
		draw_line(data, MAP_SCAL * data->px, MAP_SCAL * data->py,MAP_SCAL * cast[i].end_x, MAP_SCAL * cast[i].end_y, data->color_c);
		i++;
	}
}
void mini_map(t_data *data, t_cast *cast)
{

	int i;
	int j;
	
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0'){
				draw_rectangle(data, MAP_SCAL * (j * TILE_SIZE), MAP_SCAL * (i * TILE_SIZE), MAP_SCAL* TILE_SIZE + 1, 0xffffff);
			}
			else if (ft_isspace(data->map[i][j]))
				draw_rectangle(data, MAP_SCAL * (j * TILE_SIZE), MAP_SCAL * (i * TILE_SIZE),MAP_SCAL* TILE_SIZE + 1, 0x0000ff);
			else 
				draw_rectangle(data, MAP_SCAL * (j * TILE_SIZE), MAP_SCAL * (i * TILE_SIZE),MAP_SCAL* TILE_SIZE + 1, 0x000000);
			j++;
		}
		i++;
	}
	draw_rectangle(data, MAP_SCAL * (data->px - 10), MAP_SCAL * (data->py - 10), MAP_SCAL * 20, 0xff0000);
	cast_rays(data, cast);
}

