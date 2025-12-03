#include "header.h"



bool check_wall(char **map,double x, double y, int rows)
{
    int map_x = floor(x / TILE_SIZE);
    int map_y = floor(y / TILE_SIZE);

    if (map_x < 0 || map_y < 0 || map_y >= rows || map_x >= (int)ft_strlen(map[map_y]))
        return true;
    return (map[map_y][map_x] != '0');
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
void mini_map(t_data *data)
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
	cast_rays(data);
}
int render(t_data *data)
{
	cast(data);
	// mini_map(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img_p, 0, 0);
	return 0;
}
