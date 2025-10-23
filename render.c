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
