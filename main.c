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
#define ROTATION_SPEED 0.2

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

void *img_p;
char *img_s;
int bpp, size_of_one_row, endian;

void set_color(int x, int y,int color)
{
    // if (x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
    //     return ;

    int *row = (int *)(img_s + y * size_of_one_row);
    row[x] = color;
}

void rect(int x, int y, int color, int tile_size){

	int i = x;
	while(i < x + tile_size)
	{
		int j = y;
		while(j < y + tile_size){
			set_color(i, j, color);
			j++;
		}
		i++;
	}
}

void    line(int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        set_color(x0, y0, color);
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

void castRays(int x, int y){

	double rayAngle = rotationAngle - (FOV_ANGLE / 2);
	for (int i = 0; i < NUM_RAYS; i++){

		int line_end_x = x + (int)(cos(rayAngle) * 60);
    	int line_end_y = y + (int)(sin(rayAngle) * 60);
		line(x, y, line_end_x, line_end_y, 0xff0000);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}

void render(t_info *info)
{
	for (int i = 0; i < MAP_NUM_ROWS; i++){
		for (int j = 0; j < MAP_NUM_COLS; j++){
			if (arr[i][j] == 1){
				rect(j * TILE_SIZE, i * TILE_SIZE, 0x000000, TILE_SIZE);
			}
			else if (arr[i][j] == 0){
				rect(j * TILE_SIZE, i * TILE_SIZE, 0xffffff, TILE_SIZE);
			}
		}
	}
	rect(x_p - 10, y_p - 10, 0xff0000, 20);
	int line_end_x = x_p + (int)(cos(rotationAngle) * 30);
    int line_end_y = y_p + (int)(sin(rotationAngle) * 30);
    line( x_p, y_p, line_end_x, line_end_y, 0xff0000);
	castRays(x_p, y_p);
	mlx_put_image_to_window(info->mlx, info->win, img_p, 0, 0);
}

int is_validDer(int x, int y){

	x = floor(x / TILE_SIZE);
	y = floor(y / TILE_SIZE);

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

	info.mlx = mlx_init();
	img_p = mlx_new_image(info.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img_s = mlx_get_data_addr(img_p, &bpp, &size_of_one_row, &endian);

	info.win = mlx_new_window(info.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "title");
	render(&info);
	mlx_hook(info.win, 2, 1L<<0, movement, &info);
	mlx_loop(info.mlx);
}
