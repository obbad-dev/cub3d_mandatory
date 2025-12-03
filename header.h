#ifndef HEADER_H
#define HEADER_H
#include "minilibx-linux/mlx.h"
#include "gnl/get_next_line.h"

#include <math.h>
#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <string.h>

#define MOVE_SPEED 5
#define TILE_SIZE 64
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
	bool is_hor;
	bool facing_up;
	bool facing_down;
	bool facing_right;
	bool facing_left ;

}t_cast;

typedef struct s_textures
{
	char *id;
	char *path;
}t_textures;

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
	int	begin_map;
	int color_c;
	int color_f;
	char **map;
	int rows;
	t_textures tex[4];
	char direction;
	void *no;
	void *so;
	void *we;
	void *ea;
	double  last_time;
    double  delta_time;
    double  fps;
	t_cast cast[NUM_RAYS];

} t_data;
void draw_window(t_data *data);
int how_line_in_file(char *);
int 	mov_player(int key, t_data *data);
int	render(t_data *data);
void    draw_line(t_data *data,int x0, int y0, int x1, int y1, int color);
void 	draw_rectangle(t_data *data, int x, int y, int tile_size,int color);
void drawFilledRectangle(t_data *data, int x, int y, int width, int height, int color);
void 	put_color(t_data *data, int x, int y, int color);
void 	cast(t_data *data);
bool 	check_wall(char **map, double x, double y, int rows);
double handle_angle(double angle);
void 	dda_algo(t_data *data,int i);
void	horizonlat_inter(t_data *data, int i, double *end_hor_x, double *end_hor_y);
void	vertical_inter(t_data *data, int i, double *end_ver_x, double *end_ver_y);
void render3d(t_data *data, t_cast *cast, int i);
char	**ft_split(const char *s, char c);
long ft_atoi(char *nb, int *flag);
void	ft_print_error(char *str);

int	ft_strcmp(const char *s1, const char *s2);
bool check_line_is_one(char *line, int *begin_map);
void skip_spaces(char *line, int *j);
int ft_isspace(int c);
bool check_if_double_id(t_textures *tex, char *str);
bool check_if_malloc_fail(t_textures* tex);
void free_all(char **map);
void free_texture(t_textures *tex, char **content);

char **fill_content(char *file, int *size);

int		handle_textures(char *line, int j, t_data *data, int *k);
void	validate_colors(t_data *data, char **content);
void	validate_textures(t_data *data, char **content, int k);
bool check_parse_textures_is_valide(t_textures *tex, t_data *data);
int		handle_colors(char *line, int j, t_data *data);
void	extract_textures_colors(char **content, t_data *data);
int count_line_map(char **content);
void parse_map(char **content, t_data *data);

#endif