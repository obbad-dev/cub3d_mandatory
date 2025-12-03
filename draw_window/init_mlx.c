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
void pos_player(t_data *data)
{
	data->px = TILE_SIZE * ft_strlen(data->map[0]) / 2;
	data->py = TILE_SIZE * count_line_map(data->map) / 2;
	// while (!check_wall(data->map, data->px, data->py, data->rows))
	// {
	// 	data->px++;
	// 	// data->py++;
	// }
}
void destroy_imgs(t_data *data)
{
	if (data->ea)
		mlx_destroy_image(data->mlx,data->ea);
	if (data->we)
		mlx_destroy_image(data->mlx,data->we);
	if (data->so)
		mlx_destroy_image(data->mlx,data->so);
	if (data->no)
		mlx_destroy_image(data->mlx, data->no);
	free(data->mlx);
}
void draw_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free_texture(data->tex, data->map), free(data->mlx), ft_print_error("Error in mlx_init\n"));
	if (!check_parse_textures_is_valide(data->tex, data))
	{
		ft_print_error("Error\ninvalid path of textures\n");
		free_texture(data->tex, data->map);
		destroy_imgs(data);
		exit(1);
	}
    data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	data->img_p = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img_s = mlx_get_data_addr(data->img_p, &data->bpp, &data->size_line, &data->endian);
	pos_player(data);
	data->angle_direction =  get_direction(data->direction);
	render(data);
	mlx_hook(data->win,2, 1L<<0, mov_player, data);
    mlx_loop(data->mlx);
}
