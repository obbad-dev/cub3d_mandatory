#include "../header.h"

void	init_hor_inter(t_data *data, t_cast *cast, double *x, double *y)
{
	*y = floor(data->py / TILE_SIZE) * TILE_SIZE;
	if (cast->facing_down)
		*y += TILE_SIZE;
	*x = data->px + (*y - data->py) / tan(cast->ray_angle);
}

void	init_hor_step(t_cast *cast, double *xs, double *ys)
{
	*ys = TILE_SIZE;
	if (cast->facing_up)
		*ys *= -1;
	*xs = fabs(TILE_SIZE / tan(cast->ray_angle));
	if (cast->facing_left)
		*xs *= -1;
}

void	horizonlat_inter(t_data *data, t_cast *cast, double *end_hor_x, double *end_hor_y)
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;

	init_hor_inter(data, cast, &x, &y);
	init_hor_step(cast, &x_step, &y_step);
	if (cast->facing_up)
		y--;
	while (1)
	{
		if (check_wall(data->map, x, y, data->rows))
		{
			*end_hor_x = x;
			*end_hor_y = y;
			return ;
		}
		x += x_step;
		y += y_step;
	}
}
