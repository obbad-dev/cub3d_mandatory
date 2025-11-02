#include "header.h"

void cast(t_data *data)
{
    data->fov = 60 * (M_PI / 180);
    double rayAngle = data->rotation_angle - (data->fov / 2);

    int i = 0;
    while (i < NUM_RAYS)
    {
        data->ray_id = i++;
        DDA(data, rayAngle);
        // draw_line(data, MAP_SCAL * data->px, MAP_SCAL * data->py, MAP_SCAL * data->end_x, MAP_SCAL * data->end_y, 0x0000ff);
        rayAngle += data->fov / NUM_RAYS;
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


