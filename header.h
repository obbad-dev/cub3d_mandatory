/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:33:38 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:39:18 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "gnl/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define MOVE_SPEED 2
# define TILE_SIZE 64
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define NUM_RAYS 1920
# define ROTATION_SPEED 0.02

# define M_PI 3.14159265358979323846

# define FALSE 0
# define TRUE 1

typedef enum s_key
{
	KYS_A = 97,
	KYS_S = 115,
	KYS_D = 100,
	KYS_W = 119,
	KYS_LEFT = 65361,
	KYS_RIGHT = 65363,
	k_ESC = 65307
}				t_key;

typedef enum s_move
{
	MOVE_UP = 2,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATION_LEFT,
	ROTATION_RIGHT
}				t_move;

typedef struct s_keys
{
	bool		kys_a;
	bool		kys_s;
	bool		kys_d;
	bool		kys_w;
	bool		kys_left;
	bool		kys_right;
	bool		kys_esc;
}				t_keys;

typedef struct s_cast
{
	int			end_x;
	int			end_y;
	double		distance;
	double		ray_angle;
	bool		is_hor;
	bool		facing_up;
	bool		facing_down;
	bool		facing_right;
	bool		facing_left;
	double		dist_proj_plan;
	double		dist_perpo;
	int			tall_wall;
	int			true_begin_wall;
	int			wall_begin;
	int			wall_end;
	int			y;
	int			tex_x;
	int			tex_y;
	void		*img;
}				t_cast;

typedef struct s_textures
{
	char		*id;
	char		*path;
}				t_textures;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	double		px;
	double		py;
	double		angle_direction;
	double		fov;
	void		*img_p;
	char		*img_s;
	int			bpp;
	int			size_line;
	int			endian;
	int			ray_id;
	int			begin_map;
	int			color_c;
	int			color_f;
	char		**map;
	int			rows;
	t_textures	tex[4];
	t_keys		keys;
	char		direction;
	void		*no;
	void		*so;
	void		*we;
	void		*ea;

}				t_data;

//=========================== RENDERING =======================
void			render3d(t_data *data, t_cast *cast);
void			draw_window(t_data *data);
int				put_img_to_window(t_data *data);
int				get_pixel_color(void *texture_img, int x, int y);
void			put_color(t_data *data, int x, int y, int color);
void			dda_and_rendring(t_data *data);

// ======================== player_mouvement =================
int				key_release(t_key key, t_keys *keys);
int				key_press(t_key key, t_keys *keys);
void			mov_player(t_data *data);
bool			check_wall(char **map, double x, double y, int rows);

// ======================= DDA ALGORYTHME ====================
void			dda_algo(t_data *data, t_cast *cast);
void			horizonlat_inter(t_data *data, t_cast *cast, double *end_hor_x,
					double *end_hor_y);
void			vertical_inter(t_data *data, t_cast *cast, double *end_ver_x,
					double *end_ver_y);

// ======================= PARSING =========================
long			ft_atoi(char *nb, int *flag);
int				how_line_in_file(char *file);
char			**ft_split(const char *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
bool			check_line_is_one(char *line, int *begin_map);
void			skip_spaces(char *line, int *j);
int				ft_isspace(int c);
bool			check_if_double_id(t_textures *tex, char *str);
bool			check_if_malloc_fail(t_textures *tex);
char			**fill_content(char *file, int *size);
int				handle_textures(char *line, int j, t_data *data, int *k);
void			validate_colors(t_data *data, char **content);
void			validate_textures(t_data *data, char **content, int k);
bool			check_parse_textures_is_valide(t_textures *tex, t_data *data);
int				handle_colors(char *line, int j, t_data *data);
void			extract_textures_colors(char **content, t_data *data);
int				count_line_map(char **content);
void			parse_map(char **content, t_data *data);

// ===================== CLEANUP FUNCTIONS ================
void			ft_print_error(char *str);
void			free_all(char **map);
void			free_texture(t_textures *tex, char **content);
void			destroy_imgs(t_data *data);
void			free_destroy_all(t_data *data);

#endif