#include "../header.h"

double distance(double x1, double y1, double x2, double y2)
{
	double res;

	res = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	return res;
}

void facing_player(t_cast *cast)
{
	if (cast->ray_angle > M_PI && cast->ray_angle < 2 * M_PI)
		cast->facing_up = true;
	else
		 cast->facing_up = false;
	cast->facing_down = !cast->facing_up;

	if (cast->ray_angle < (M_PI / 2) || cast->ray_angle > (3 * M_PI / 2))
		cast->facing_right = true;
	else
		cast->facing_right = false;
	cast->facing_left = !cast->facing_right;
}

void	set_hit(t_cast *c, double x, double y, double d)
{
	c->end_x = x;
	c->end_y = y;
	c->distance = d;
}

void	dda_algo(t_data *data, int i)
{
	double	end_hor_x;
	double	end_hor_y;
	double	end_ver_x;
	double	end_ver_y;
	double	dist_hor;
	double	dist_ver;

	facing_player(&data->cast[i]);
	horizonlat_inter(data, i, &end_hor_x, &end_hor_y);
	vertical_inter(data, i, &end_ver_x, &end_ver_y);
	dist_hor = distance(data->px, data->py, end_hor_x, end_hor_y);
	dist_ver = distance(data->px, data->py, end_ver_x, end_ver_y);
	data->cast[i].is_hor = false;
	if (dist_hor < dist_ver)
	{
		set_hit(&data->cast[i], end_hor_x, end_hor_y, dist_hor);
		data->cast[i].is_hor = true;
	}
	else
		set_hit(&data->cast[i], end_ver_x, end_ver_y, dist_ver);
	render3d(data, &data->cast[i], i);
}


