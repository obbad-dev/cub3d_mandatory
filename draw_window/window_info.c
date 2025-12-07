/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:24:18 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:43:52 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

double	get_direction(char dir)
{
	if (dir == 'N')
		return (3 * M_PI / 2);
	else if (dir == 'S')
		return (M_PI / 2);
	else if (dir == 'W')
		return (M_PI);
	else
		return (0);
}

void	init_keys(t_keys *key)
{
	key->kys_a = false;
	key->kys_w = false;
	key->kys_s = false;
	key->kys_d = false;
	key->kys_left = false;
	key->kys_right = false;
	key->kys_esc = false;
}

int	game_loop(t_data *data)
{
	put_img_to_window(data);
	mov_player(data);
	return (0);
}

int	destroy_notify(t_data *data)
{
	free_destroy_all(data);
	exit(0);
}

void	draw_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free_texture(data->tex, data->map), free(data->mlx),
			ft_print_error("Error in mlx_init\n"));
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	data->img_p = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img_s = mlx_get_data_addr(data->img_p, &data->bpp, &data->size_line,
			&data->endian);
	if (!check_parse_textures_is_valide(data->tex, data))
	{
		ft_print_error("Error\ninvalid path of textures\n");
		free_destroy_all(data);
		exit(1);
	}
	init_keys(&data->keys);
	data->angle_direction = get_direction(data->direction);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, &data->keys);
	mlx_hook(data->win, 3, 1L << 1, key_release, &data->keys);
	mlx_hook(data->win, 17, 0, destroy_notify, data);
	mlx_loop(data->mlx);
}
