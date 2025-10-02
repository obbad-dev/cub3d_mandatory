#ifndef HEADER_H
#define HEADER_H
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h> 
#include <stdio.h>

#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define TILE_SIZE 64
#define WIN_WIDTH (MAP_NUM_COLS*TILE_SIZE)
#define WIN_HIEGHT (MAP_NUM_ROWS*TILE_SIZE)
#define X_PLAYER (WIN_WIDTH/2)
#define Y_PLAYER (WIN_HIEGHT/2)

typedef struct s_data
{
	void 	*mlx;
	void 	*win;
	double 	px;
	double 	py;
	double  rotation_angle;
    double  dirx;
    double  diry;
    double  planex;   
    double  planey;
	void 	*img_p;
	char 	*img_s;
	int 	bpp;
	int 	size_line;
	int 	endian;

} t_data;



#endif