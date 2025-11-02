#include "header.h"

int arr[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

bool check_wall(double x, double y)
{
    int map_x = floor(x / TILE_SIZE);
    int map_y = floor(y / TILE_SIZE);

    if (map_x < 0 || map_x >= MAP_NUM_COLS || map_y < 0 || map_y >= MAP_NUM_ROWS)
        return true;
    return (arr[map_y][map_x] == 1);
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

	draw_rectangle(data, data->px - 10, data->py - 10, 20,0xff0000);
	cast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_p, 0, 0);
}
