/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ver_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:23:50 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:23:51 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	init_ver_inter(t_data *data, t_cast *cast, double *x, double *y)
{
	*x = floor(data->px / TILE_SIZE) * TILE_SIZE;
	if (cast->facing_right)
		*x += TILE_SIZE;
	*y = data->py + (*x - data->px) * tan(cast->ray_angle);
}

void	init_ver_step(t_cast *cast, double *xs, double *ys)
{
	*xs = TILE_SIZE;
	if (cast->facing_left)
		*xs *= -1;
	*ys = fabs(tan(cast->ray_angle) * TILE_SIZE);
	if (cast->facing_up)
		*ys *= -1;
}

void	vertical_inter(t_data *data, t_cast *cast, double *end_ver_x,
		double *end_ver_y)
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;

	init_ver_inter(data, cast, &x, &y);
	init_ver_step(cast, &x_step, &y_step);
	if (cast->facing_left)
		x--;
	while (1)
	{
		if (check_wall(data->map, x, y, data->rows))
		{
			*end_ver_x = x;
			*end_ver_y = y;
			return ;
		}
		x += x_step;
		y += y_step;
	}
}
