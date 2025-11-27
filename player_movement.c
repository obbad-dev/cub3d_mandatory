#include "header.h"

int mov_player(int key, t_data *data)
{
	
	int walk = 0;
	int turn = 0;
	int izaha = 0;

	if (key == 65362)
		walk = 1;
	else if (key == 65364)
		walk = -1;
	else if (key == 65361)
		turn = -1;
	else if (key ==  65363)
		turn = 1;
	else if (key == 'a')
		izaha = -1;
	else if (key == 'd')
		izaha = 1;
	else if (key == 65307)
		exit(1);
	
	data->angle_direction += turn * 0.2; 
    int moveStep = walk * MOVE_SPEED; 
	int move = izaha * MOVE_SPEED;
	double x = 0, y = 0;

	x = data->px + cos(data->angle_direction) * moveStep;
	y = data->py + sin(data->angle_direction) * moveStep;
	if (izaha)
	{
		x = data->px + cos(data->angle_direction + M_PI / 2) * move;
		y = data->py + sin(data->angle_direction + M_PI / 2) * move;
	}
	if (!check_wall(data->map,x, y, data->rows)){
		data->px = x; 
		data->py = y;
	}
	render(data);
	return key;
}