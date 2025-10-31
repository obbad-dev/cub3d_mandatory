#include "header.h"

double distance(double x1, double y1, double x2, double y2)
{
	double res;

	res = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	return res;
}

double handle_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return angle;
}
void facing_player(bool *facing_up, bool *facing_down, bool *facing_left, bool *facing_right, double rayAngle)
{
	if (rayAngle > M_PI && rayAngle < 2 * M_PI)
		*facing_up = true;
	else
		*facing_up = false;
	*facing_down = !*facing_up;

//============================================================================
	if (rayAngle < (M_PI / 2) || rayAngle > (3 * M_PI / 2))
		*facing_right = true;
	else
		*facing_right = false;
	*facing_left = !*facing_right;
}

void DDA(t_data *data, double rayAngle)
{
	double x_inter;
	double y_inter;
	double x_step;
	double y_step;
	double end_hor_x;
	double end_hor_y;
	double end_ver_x;
	double end_ver_y;
	bool facing_up;
	bool facing_down;
	bool facing_right;
	bool facing_left ;

	rayAngle = handle_angle(rayAngle);
	facing_player(&facing_up, &facing_down, &facing_left, &facing_right, rayAngle);

//=================================| Horizontal |======================================

	y_inter = floor(data->py / TILE_SIZE) * TILE_SIZE;
	if (facing_down)
		y_inter += TILE_SIZE;

	x_inter = data->px + (y_inter - data->py) / tan(rayAngle);

	y_step = TILE_SIZE;
	if (facing_up)
		y_step *= -1;

	x_step = fabs(TILE_SIZE / tan(rayAngle));
	if (facing_left)
		x_step *= -1;

	if (facing_up)
		y_inter--;

	while (1)
	{
		if (check_wall(x_inter, y_inter))
		{
			end_hor_x = x_inter;
			end_hor_y = y_inter;
			break;
		}
		x_inter += x_step;
		y_inter += y_step;
	}

//=================================| Vertical |======================================

	x_inter = floor(data->px / TILE_SIZE) * TILE_SIZE;
	if (facing_right)
		x_inter += TILE_SIZE;

	y_inter = data->py + (x_inter - data->px) * tan(rayAngle);

	x_step = TILE_SIZE;
	if (facing_left)
		x_step *= -1;

	y_step = fabs(tan(rayAngle) * TILE_SIZE);
	if (facing_up)
		y_step *= -1;

	if (facing_left)
		x_inter--;

	while (1)
	{
		if (check_wall(x_inter, y_inter))
		{
			end_ver_x = x_inter;
			end_ver_y = y_inter;
			break;
		}
		x_inter += x_step;
		y_inter += y_step;
	}

//=================================| calculate distance |======================================

	double dist_hor = distance(data->px, data->py, end_hor_x, end_hor_y);
	double dist_ver = distance(data->px, data->py, end_ver_x, end_ver_y);

	int end_linex;
	int end_liney;

	if (dist_hor < dist_ver)
	{
		end_linex = end_hor_x;
		end_liney = end_hor_y;
	}
	else
	{
		end_linex = end_ver_x;
		end_liney = end_ver_y;
	}

	draw_line(data, data->px, data->py, end_linex, end_liney, 0x00ff00);
}
