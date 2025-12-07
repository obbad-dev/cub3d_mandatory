/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_and_rendring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:24:11 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:24:12 by oobbad           ###   ########.fr       */
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
	t_cast	cast;

	i = 0;
	data->fov = 60 * (M_PI / 180);
	cast.dist_proj_plan = (WIN_WIDTH / 2) / tan(data->fov / 2);
	ray_angle = data->angle_direction - (data->fov / 2);
	while (i < NUM_RAYS)
	{
		cast.ray_angle = handle_angle(ray_angle);
		dda_algo(data, &cast);
		render3d(data, &cast);
		ray_angle += data->fov / NUM_RAYS;
		i++;
	}
}

int	put_img_to_window(t_data *data)
{
	dda_and_rendring(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img_p, 0, 0);
	return (0);
}

// void cast_ray(t_data *data, double rayAngle)
// {

//     double x = data->px;
//     double y = data->py;
//     double each_distance = 1;

//     while (1)
//     {
//         x += cos(rayAngle) * each_distance;
//         y += sin(rayAngle) * each_distance;

//         if (check_wall(x, y))
//         {
//             draw_line(data, data->px, data->py, x, y, 0xff0000);
//             break ;
//         }
//     }
// }
