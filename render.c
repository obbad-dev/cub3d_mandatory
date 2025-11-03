#include "header.h"

int arr[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 4, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 4, 0, 1},
	{1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 4, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

bool check_wall(double x, double y)
{
    int map_x = floor(x / TILE_SIZE);
    int map_y = floor(y / TILE_SIZE);

    if (map_x < 0 || map_x >= MAP_NUM_COLS || map_y < 0 || map_y >= MAP_NUM_ROWS)
        return true;
    return (arr[map_y][map_x] != 0);
}

int check_wall_number(double x, double y)
{
    int map_x = floor(x / TILE_SIZE);
    int map_y = floor(y / TILE_SIZE);

    if (map_x < 0 || map_x >= MAP_NUM_COLS || map_y < 0 || map_y >= MAP_NUM_ROWS)
        return 1;
	else if (arr[map_y][map_x] == 4)
		return 4;
	else if (arr[map_y][map_x] == 1)
		return 1;
	else
    	return 0;
}

void cast_rays(t_data *data)
{
	t_cast *cast;
	int i;

	cast = data->cast;
	i = 0;
	while(i < NUM_RAYS)
	{
		draw_line(data, MAP_SCAL * data->px, MAP_SCAL * data->py,MAP_SCAL * cast[i].end_x, MAP_SCAL * cast[i].end_y, 0x00ff00);
		i++;
	}
}
void render(t_data *data)
{
	int i;
	int j;
	
	i = 0;
	update_fps(data);
	cast(data);
	while (i < MAP_NUM_ROWS){
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (arr[i][j] == 0){
				draw_rectangle(data, MAP_SCAL * (j * TILE_SIZE), MAP_SCAL * (i * TILE_SIZE), MAP_SCAL* TILE_SIZE + 1, 0xffffff);
			}
			else
				draw_rectangle(data, MAP_SCAL * (j * TILE_SIZE), MAP_SCAL * (i * TILE_SIZE),MAP_SCAL* TILE_SIZE + 1, 0x000000);
			j++;
		}
		i++;
	}
	draw_rectangle(data, MAP_SCAL * (data->px - 10), MAP_SCAL * (data->py - 10), MAP_SCAL * 20, 0xff0000);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_p, 0, 0);
}
