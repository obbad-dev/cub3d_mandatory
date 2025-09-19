#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h> 
#include <stdio.h>

typedef struct s_info
{
	void *mlx;
	void *win;
	void *img_wall;
	void *img_floor;
	void *img_player;
	int x_player;
	int y_player;

} t_info;

#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define TILE_SIZE 64
#define MOVE_SPEED 10
#define ROTATION_SPEED 0.1

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_UP 65362
#define KEY_BOTTOM 65364
#define KEY_ESC 65307

double rotationAngle = M_PI /2;

const int WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const int WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;

const double FOV_ANGLE = 60 * (M_PI / 180.0);
 
const int WALL_STRIP_WIDTH = 1;
const int NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH;

int x_p = WINDOW_WIDTH/2;
int y_p = WINDOW_HEIGHT/2;

int arr[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// function castAllRays(){
// 	var columndId = 0;
// 	var rayAngle = player.rotationAngel - (FOV_ANGLE / 2);
// 	rays = [];
// 	for (var i = 0; i <NUM_RAYS; i++){
// 		var ray = new Ray(rayAngle);
// 		rays.push(ray);
// 		rayAngle += FOV_ANGLE / NUM_RAYS;
// 		columndId++;
// 	}
// }

void rect(t_info *info, int x, int y, int color, int tile_size){

	
	int i = x;
	while(i < x + tile_size)
	{
		int j = y;
		while(j < y + tile_size){
			mlx_pixel_put(info->mlx, info->win, i , j, color);
			j++;
		}
		i++;
	}
}


void    line(t_info *info, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_pixel_put(info->mlx, info->win, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
void castRays(t_info *info, int x, int y){
	
	double rayAngle = rotationAngle - (FOV_ANGLE / 2);
	for (int i = 0; i < NUM_RAYS; i++){

		int line_end_x = x + (int)(cos(rayAngle) * 30);
    	int line_end_y = y + (int)(sin(rayAngle) * 30);
		line(info, x, y, line_end_x, line_end_y, 0xff0000);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}

}
void render(t_info *info)
{
	
	for (int i = 0; i < MAP_NUM_ROWS; i++){
		for (int j = 0; j < MAP_NUM_COLS; j++){
			if (arr[i][j] == 1){
				rect(info, j * 64, i * 64, 0x000000, TILE_SIZE);
			}
			else if (arr[i][j] == 0)
				rect(info,  j * 64, i * 64, 0xffffff, TILE_SIZE);
		}
	}
	rect(info, x_p - 10, y_p - 10, 0xff0000, 20);
	int line_end_x = x_p + (int)(cos(rotationAngle) * 30);
    int line_end_y = y_p + (int)(sin(rotationAngle) * 30);
    line(info, x_p, y_p, line_end_x, line_end_y, 0xff0000);
	castRays(info, x_p, y_p);
}

int is_validDer(int x, int y){
	x /= TILE_SIZE;
	y /= TILE_SIZE;
	x = floor(x);
	y = floor(y);

	if (arr[y][x] == 1){
		return 0;
	}
	else
		return 1;
}

int movement(int key, t_info *info){

	int turnDerction = 0;
	int walkDerection = 0;
	
	if (key == KEY_UP){
		walkDerection = 1;
	}
	else if (key == KEY_BOTTOM){
		walkDerection = -1;
	}
	else if (key == KEY_LEFT){
		turnDerction = -1;
	}
	else if (key == KEY_RIGHT){
		turnDerction = 1;
	}
	rotationAngle += turnDerction * ROTATION_SPEED;
	int moveStep = walkDerection * MOVE_SPEED;

	int x = x_p + cos(rotationAngle) * moveStep;
	int y = y_p + sin(rotationAngle) * moveStep;
	if (is_validDer(x, y)){
		x_p = x;
		y_p = y;
	}
	render(info);
	return 0;
}

int main()
{
	t_info info;
	int width;
	int hieght;

	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "title");
	info.img_floor = mlx_xpm_file_to_image(info.mlx, "texture/floor.xpm", &width, &hieght);
	info.img_wall = mlx_xpm_file_to_image(info.mlx, "texture/wall.xpm", &width, &hieght);
	render(&info);
	mlx_hook(info.win, 2, 1L<<0, movement, &info);
	mlx_loop(info.mlx);
}
