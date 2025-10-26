#include "header.h"

double distance(double x1, double y1, double x2, double y2){
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

	int facing_up = rayAngle > 0 && rayAngle < M_PI;
	int facing_down = !facing_up;

	int facing_right = rayAngle < (M_PI/2) || rayAngle > (3 * M_PI/2);
	int facing_left = !facing_right;
	
	rayAngle = handle_angle(rayAngle);

//=================================| Horizontal |======================================


	y_inter = floor(data->py/TILE_SIZE) * TILE_SIZE;
	y_inter += facing_down ? TILE_SIZE  : 0; 

	x_inter = data->px + (y_inter - data->py)/tan(rayAngle);

	y_step = TILE_SIZE;
	y_step *= facing_up ? -1: 1;

	x_step = y_step/tan(rayAngle);
	x_step *= (facing_left && x_step > 0) ? -1 : 1;
	x_step *= (facing_right && x_step < 0) ? -1 : 1;

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
		else
		{
			x_inter += x_step;
			y_inter += y_step;
		}
	}

//=================================| vertical |======================================
	x_inter = floor(data->px/TILE_SIZE) * TILE_SIZE;
	x_inter += facing_right ? TILE_SIZE : 0;


	y_inter = data->py + (x_inter - data->px) * tan(rayAngle);

	x_step = TILE_SIZE;
	x_step *= facing_left ? -1 : 1;

	y_step = tan(rayAngle) * x_step;
	y_step *= (facing_down && y_step < 0) ? -1 : 1;
	y_step *= (facing_up && y_step > 0) ? -1 : 1;

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
		else
		{
			x_inter += x_step;
			y_inter += y_step;
		}
	}

	double dist_hor;
	double dist_ver;

	dist_hor = distance(data->px, data->py, end_hor_x, end_hor_y);
	dist_ver = distance(data->px, data->py, end_ver_x, end_ver_y);

	int end_linex;
	int end_liney;
	
	if (dist_hor < dist_ver){
		end_linex = end_hor_x;
		end_liney = end_hor_y;
	}else
	{
		end_linex = end_ver_x;
		end_liney = end_ver_y;
	}
	draw_line(data, data->px, data->py, end_linex, end_liney, 0x00ff00);

}































































// void DDA(t_data *data, double rayAngle)
// {	
// 	double rayDirX = cos(rayAngle);
// 	double rayDirY = sin(rayAngle);

// 	double deltaDistX = fabs(1 / rayDirX);
// 	double deltaDistY = fabs(1 / rayDirY);

// 	int x = (int)data->px; 
// 	int y = (int)data->py; 

// 	int stepX = 0;
// 	int stepY = 0;
// 	double sideDistX = 0;
// 	double sideDistY = 0;

// 	if (rayDirX < 0)
// 	{
// 		stepX = -1;
// 		sideDistX = (data->px - x) * deltaDistX;
// 	}
// 	else 
// 	{
// 		stepX = 1;
// 		sideDistX = (x + 1.0 - data->px) * deltaDistX;
// 	}

// 	if (rayDirY < 0)
// 	{
// 		stepY = -1;
// 		sideDistY = (data->py - y) * deltaDistY;
// 	}
// 	else 
// 	{
// 		stepY = 1;
// 		sideDistY = (y + 1.0 - data->py) * deltaDistY;
// 	}

// 	int side = 0;

// 	while (1)
// 	{
// 		if (sideDistX < sideDistY)
// 		{
// 			sideDistX += deltaDistX;
// 			x += stepX;
// 			side = 0;
// 		}
// 		else
// 		{
// 			sideDistY += deltaDistY;
// 			y += stepY;
// 			side = 1;
// 		}
// 		if (check_wall(x, y)) 
// 			break;
// 	}

	
// }


