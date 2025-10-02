#include "header.h"

int arr[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void put_color(t_data *data, int x, int y, int color)
{
	int *row;

	row = (int *)(data->img_s + y * data->size_line);
	row[x] = color;
}

void    line(t_data *data,int x0, int y0, int x1, int y1, int color)
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

void draw_rectangle(t_data *data, int x, int y, int tile_size,int color){
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

void render(t_data *data)
{
	int i;
	int j;

	i = 0; 
	while (i < MAP_NUM_ROWS){
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (arr[i][j] == 1){
				draw_rectangle(data, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, 0x000000);
			}
			else if (arr[i][j] == 0)
				draw_rectangle(data, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, 0xffffff);
			j++;
		}
		i++;
	}
	draw_rectangle(data, data->px, data->py, 20,0xff0000);
	int line_end_x = data->px + (int)(cos(data->rotation_angle) * 30);
    int line_end_y = data->py + (int)(sin(data->rotation_angle) * 30);
	line(data, data->px + 10, data->py + 10, line_end_x + 10, line_end_y + 10, 0x0000ff);
	mlx_put_image_to_window(data->mlx, data->win, data->img_p, 0, 0);
}

int main()
{
	t_data data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HIEGHT, "My First MLX Window");
	data.img_p = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HIEGHT);
	data.img_s = mlx_get_data_addr(data.img_p, &data.bpp, &data.size_line, &data.endian);
	data.px = WIN_WIDTH / 2;
	data.py = WIN_HIEGHT / 2;
	data.rotation_angle = M_PI /2;
	mlx_hook(data.win,2, 1L<<0, mov_player, &data);
	render(&data);
    mlx_loop(data.mlx); 
    return (0);
}
