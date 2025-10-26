#ifndef HEADER_H
#define HEADER_H
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define TILE_SIZE 64
#define WIN_WIDTH (MAP_NUM_COLS*TILE_SIZE)
#define WIN_HEIGHT (MAP_NUM_ROWS*TILE_SIZE)
#define X_PLAYER (WIN_WIDTH/2)
#define Y_PLAYER (WIN_HEIGHT/2)
#define NUM_RAYS 1080
#define TWO_PI 6.28318530

typedef struct s_data
{
	void 	*mlx;
	void 	*win;
	double 	px;
	double 	py;
	double  rotation_angle;
	void 	*img_p;
	char 	*img_s;
	int 	bpp;
	int 	size_line;
	int 	endian;

} t_data;

int 	mov_player(int key, t_data *data);
void 	render(t_data *data);
void    draw_line(t_data *data,int x0, int y0, int x1, int y1, int color);
void 	draw_rectangle(t_data *data, int x, int y, int tile_size,int color);
void 	put_color(t_data *data, int x, int y, int color);
void 	cast(t_data *data);
bool 	check_wall(double x, double y);
void 	DDA(t_data *data, double rayAngle);

extern int arr[MAP_NUM_ROWS][MAP_NUM_COLS];

#endif