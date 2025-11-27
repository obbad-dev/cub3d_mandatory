#include "../header.h"

double get_direction(char dir)
{
	if (dir == 'N')
		return (3 * M_PI/2);
	else if (dir == 'S')
		return (M_PI / 2);
	else if (dir == 'W')
		return (M_PI);
	else
		return 0;
}

void draw_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!check_parse_textures_is_valide(data->tex, data))
	{
		ft_print_error("Error\ninvalid path of textures\n");
		free_texture(data->tex, data->map);
		exit(1);
	}
    data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	data->img_p = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img_s = mlx_get_data_addr(data->img_p, &data->bpp, &data->size_line, &data->endian);
	data->px = TILE_SIZE * MAP_NUM_COLS / 2;
	data->py = TILE_SIZE * MAP_NUM_ROWS / 2;
	data->angle_direction =  get_direction(data->direction);
	render(data);
	mlx_hook(data->win,2, 1L<<0, mov_player, data);
    mlx_loop(data->mlx);
}