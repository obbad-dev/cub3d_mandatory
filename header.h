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
#define TILE_SIZE 32
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define NUM_RAYS 1920
#define MAP_SCAL 0.2

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
typedef struct s_cast
{
	int end_x;
	int end_y;
	double distance;
	double ray_angle;

}t_cast;

typedef struct s_data
{
	void 	*mlx;
	void 	*win;
	double 	px;
	double 	py;
	double  angle_direction;
	double fov;
	void 	*img_p;
	char 	*img_s;
	int 	bpp;
	int 	size_line;
	int 	endian;
	int 	ray_id;
	t_cast cast[NUM_RAYS];

} t_data;


int 	mov_player(int key, t_data *data);
void 	render(t_data *data);
void    draw_line(t_data *data,int x0, int y0, int x1, int y1, int color);
void 	draw_rectangle(t_data *data, int x, int y, int tile_size,int color);
void drawFilledRectangle(t_data *data, int x, int y, int width, int height, int color);
void 	put_color(t_data *data, int x, int y, int color);
void 	cast(t_data *data);
bool 	check_wall(double x, double y);
double handle_angle(double angle);
void 	DDA(t_data *data, double rayAngle, int i);
void render3d(t_data *data, int i);
int check_wall_number(double x, double y);
extern int arr[MAP_NUM_ROWS][MAP_NUM_COLS];

#endif