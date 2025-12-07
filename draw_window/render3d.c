/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakbour <kakbour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:24:14 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 16:31:58 by kakbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	select_texture(t_data *data, t_cast *cast)
{
	if (cast->is_hor)
	{
		cast->tex_x = cast->end_x % TILE_SIZE;
		if (cast->facing_up)
			cast->img = data->no;
		else if (cast->facing_down)
			cast->img = data->so;
	}
	else if (!cast->is_hor)
	{
		cast->tex_x = cast->end_y % TILE_SIZE;
		if (cast->facing_left)
			cast->img = data->we;
		else if (cast->facing_right)
			cast->img = data->ea;
	}
}

void	draw_all(t_data *data, t_cast *cast, int i)
{
	int	y;
	int	color;

	y = 0;
	while (y < cast->wall_begin)
	{
		put_color(data, i, y, data->color_c);
		y++;
	}
	y = cast->wall_begin;
	while (y < cast->wall_end)
	{
		cast->tex_y = (y - cast->true_begin_wall) * (64.0 / cast->tall_wall);
		color = get_pixel_color(cast->img, cast->tex_x, cast->tex_y);
		put_color(data, i, y, color);
		y++;
	}
	y = cast->wall_end;
	while (y < WIN_HEIGHT)
	{
		put_color(data, i, y, data->color_f);
		y++;
	}
}

void	compute_wall(t_cast *cast, t_data *data)
{
	cast->dist_perpo = cast->distance * cos(cast->ray_angle
			- data->angle_direction);
	cast->tall_wall = (TILE_SIZE / cast->dist_perpo) * cast->dist_proj_plan;
	cast->wall_begin = (WIN_HEIGHT / 2) - (cast->tall_wall / 2);
	cast->true_begin_wall = cast->wall_begin;
	cast->wall_end = (WIN_HEIGHT / 2) + (cast->tall_wall / 2);
	if (cast->wall_begin < 0)
		cast->wall_begin = 0;
	if (cast->wall_end > WIN_HEIGHT)
		cast->wall_end = WIN_HEIGHT;
}

void	render3d(t_data *data, t_cast *cast)
{
	static int	i;

	i = i % NUM_RAYS;
	compute_wall(cast, data);
	select_texture(data, cast);
	draw_all(data, cast, i);
	i++;
}
