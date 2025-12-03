#include "../header.h"

void	init_ver_inter(t_data *data, int i, double *x, double *y)
{
	*x = floor(data->px / TILE_SIZE) * TILE_SIZE;
	if (data->cast[i].facing_right)
		*x += TILE_SIZE;
	*y = data->py + (*x - data->px) * tan(data->cast[i].ray_angle);
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

void	vertical_inter(t_data *data, int i, double *end_ver_x, double *end_ver_y)
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;

	init_ver_inter(data, i, &x, &y);
	init_ver_step(&data->cast[i], &x_step, &y_step);
	if (data->cast[i].facing_left)
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
