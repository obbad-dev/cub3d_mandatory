#include "header.h"

double handle_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return angle;
}

int get_pixel_color(void *texture_img, int x, int y)
{
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int *pixel;

	addr = mlx_get_data_addr(texture_img, &bits_per_pixel, &line_length, &endian);
	pixel = (int *)(addr + y * line_length);

	return (pixel[x]);
}

void render3d(t_data *data, t_cast *cast, int i)
{
	double distance_projection_plan;
	double dist_perpo;
	int tall_wall;
	int wall_begin;
	int wall_end;
	int y;
	int tex_x;
	int tex_y;
	void *img;

	distance_projection_plan = (WIN_WIDTH / 2) / tan(data->fov / 2);
	dist_perpo = cast->distance * cos(cast->ray_angle - data->angle_direction);

	tall_wall = (TILE_SIZE / dist_perpo) * distance_projection_plan;

	wall_begin = (WIN_HEIGHT / 2) - (tall_wall / 2);
	wall_end = (WIN_HEIGHT / 2) + (tall_wall / 2);

	if (wall_begin < 0)
		wall_begin = 0;
	if (wall_end > WIN_HEIGHT)
		wall_end = WIN_HEIGHT;
	
	y = 0;
	while (y < wall_begin)
	{
		put_color(data, i, y, data->color_c);
		y++;
	}
	if (cast->is_hor)
	{
		tex_x = cast->end_x % TILE_SIZE;
		if (cast->facing_up)
			img = data->no;
		else
			img = data->so;
	}
	else
	{
		tex_x = cast->end_y % TILE_SIZE;
		if (cast->facing_left)
			img = data->we;
		else
			img = data->ea;
	}
	y = wall_begin;
	while (y < wall_end)
	{
		int dis = y + (tall_wall / 2) - (WIN_HEIGHT / 2);// eq (y - wall_begin) but in the right wall begin 
		tex_y = dis * (64.0 / tall_wall);
		put_color(data, i, y, get_pixel_color(img, tex_x, tex_y));
		y++;
	}
	y = wall_end;
	while (y < WIN_HEIGHT)
	{
		put_color(data, i, y, data->color_f);
		y++;
	}
}

void cast(t_data *data)
{
    double ray_angle;
	int i;

	i = 0;
    data->fov = 60 * (M_PI / 180);
    ray_angle = data->angle_direction - (data->fov / 2);
    while (i < NUM_RAYS)
    {
		data->cast[i].ray_angle = handle_angle(ray_angle);
		dda_algo(data, i);
		ray_angle +=data->fov / NUM_RAYS;
		i++;
    }
	
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
//             break;
//         }
//     }
// }


