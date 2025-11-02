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

	if (rayAngle < (M_PI / 2) || rayAngle > (3 * M_PI / 2))
		*facing_right = true;
	else
		*facing_right = false;
	*facing_left = !*facing_right;
}

void render3d(t_data *data, double rayAngle)
{
	double distance_projection_plan;
	double wall_height;
	int wall_strip_height;
	int wall_top;
	int wall_bottom;
	int y;

	// Fix fisheye effect - use perpendicular distance
	data->distance = data->distance * cos(rayAngle - data->rotation_angle);
	
	// Prevent division by zero
	if (data->distance <= 0.1)
		data->distance = 0.1;

	// Calculate projection and wall height
	distance_projection_plan = (WIN_WIDTH / 2) / tan(data->fov / 2);
	wall_height = (TILE_SIZE / data->distance) * distance_projection_plan;
	wall_strip_height = (int)floor(wall_height);

	// Calculate top and bottom positions
	wall_top = (WIN_HEIGHT / 2) - (wall_strip_height / 2);
	wall_bottom = (WIN_HEIGHT / 2) + (wall_strip_height / 2);

	// Clamp to window bounds
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > WIN_HEIGHT)
		wall_bottom = WIN_HEIGHT;

	Draw ceiling (sky)
	y = 0;
	while (y < wall_top)
	{
		put_color(data, data->ray_id, y, 0x87CEEB); // Sky blue
		y++;
	}

	// Draw wall
	y = wall_top;
	while (y < wall_bottom)
	{
		put_color(data, data->ray_id, y, 0x808080); // Gray wall
		y++;
	}

	// Draw floor
	y = wall_bottom;
	while (y < WIN_HEIGHT)
	{
		put_color(data, data->ray_id, y, 0x228B22); // Green floor
		y++;
	}
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


	if (dist_hor < dist_ver)
	{
		data->end_x = end_hor_x;
		data->end_y = end_hor_y;
		data->distance = dist_hor;
	}
	else
	{
		data->end_x = end_ver_x;
		data->end_y = end_ver_y;
		data->distance = dist_ver;

	}
	draw_line(data, MAP_SCAL * data->px, MAP_SCAL * data->py, MAP_SCAL * data->end_x, MAP_SCAL * data->end_y, 0x00ff00);
	render3d(data, rayAngle);
}
