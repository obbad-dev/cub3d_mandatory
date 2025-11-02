#include "header.h"

void cast_ray(t_data *data, double rayAngle)
{
  
    double x = data->px;
    double y = data->py;
    double each_distance = 1;

    while (1)
    {
        x += cos(rayAngle) * each_distance;
        y += sin(rayAngle) * each_distance;

        if (check_wall(x, y))
        {
            draw_line(data, data->px, data->py, x, y, 0xff0000);
            break;
        }
    }
}

void cast(t_data *data)
{
    data->fov = 60 * (M_PI / 180);
    double rayAngle = data->rotation_angle - (data->fov / 2);

    int i = 0;
    while (i < NUM_RAYS)
    {
        DDA(data, rayAngle);
        rayAngle += data->fov / NUM_RAYS;
        i++;
    }
}

