/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_and_rendring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:24:11 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/08 10:40:50 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

double	handle_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	dda_and_rendring(t_data *data)
{
	double	ray_angle;
	int		i;
	t_cast	cast[NUM_RAYS];

	i = 0;
	data->fov = 60 * (M_PI / 180);
	ray_angle = data->angle_direction - (data->fov / 2);
	while (i < NUM_RAYS)
	{
		cast[i].dist_proj_plan = (WIN_WIDTH / 2) / tan(data->fov / 2);
		cast[i].ray_angle = handle_angle(ray_angle);
		dda_algo(data, &cast[i]);
		render3d(data, &cast[i]);
		ray_angle += data->fov / NUM_RAYS;
		i++;
	}
	if (data->mini_map)
		mini_map(data, cast);
}

int	put_img_to_window(t_data *data)
{
	dda_and_rendring(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img_p, 0, 0);
	return (0);
}

