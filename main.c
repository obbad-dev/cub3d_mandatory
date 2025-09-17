#include "minilibx-linux/mlx.h"

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

int arr[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void rect(t_info *info, int x, int y, int color){

	x *= 64;
	y *= 64;

	int i = y;
	while(i < y + 64)
	{
		int j = x;
		while(j < x + 64){
			mlx_pixel_put(info->mlx, info->win, i , j, color);
			j++;
		}
		i++;
	}
}

void render(t_info *info)
{
	int width;
	int hieght;

	info->img_floor = mlx_xpm_file_to_image(info->mlx, "texture/floor.xpm", &width, &hieght);
	info->img_wall = mlx_xpm_file_to_image(info->mlx, "texture/wall.xpm", &width, &hieght);

	for (int i = 0; i < MAP_NUM_ROWS; i++){
		for (int j = 0; j < MAP_NUM_COLS; j++){
			if (arr[i][j] == 1){
				mlx_put_image_to_window(info->mlx, info->win, info->img_wall, j * 64, i * 64);
			}
			else if (arr[i][j] == 2){
				mlx_put_image_to_window(info->mlx, info->win, info->img_floor, j * 64, i * 64);
				info->x_player = j;
				info->y_player = i;
			}
			else
				mlx_put_image_to_window(info->mlx, info->win, info->img_floor, j * 64, i * 64);
		}
	}
	rect(info, info->y_player, info->x_player, 0x00ff00);
}

int main()
{
	t_info info;
	
	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, MAP_NUM_COLS*64, MAP_NUM_ROWS*64, "title");
	render(&info);
	// mlx_key_hook(info.win, movement, &info);
	mlx_loop(info.mlx);
}

// int movement(int key, t_info *info){
// 	if (key == 'd')
// 	{
// 		if (arr[info->y_player][info->x_player + 1] != 1){
// 			mlx_put_image_to_window(info->mlx, info->win, info->img_floor, info->x_player*64, info->y_player*64);
// 			info->x_player++;
// 			mlx_put_image_to_window(info->mlx, info->win, info->img_player, info->x_player*64, info->y_player*64);
// 		}
// 	}
// 	else if (key == 'a')
// 	{
// 		if (arr[info->y_player][info->x_player - 1] != 1){
// 			mlx_put_image_to_window(info->mlx, info->win, info->img_floor, info->x_player*64, info->y_player*64);
// 			info->x_player--;
// 			mlx_put_image_to_window(info->mlx, info->win, info->img_player, info->x_player*64, info->y_player*64);
// 		}
// 	}
// 	else if (key == 'w')
// 	{
// 		if (arr[info->y_player - 1][info->x_player] != 1){
// 			mlx_put_image_to_window(info->mlx, info->win, info->img_floor, info->x_player*64, info->y_player*64);
// 			info->y_player--;
// 			mlx_put_image_to_window(info->mlx, info->win, info->img_player, info->x_player*64, info->y_player*64);
// 		}
// 	}
// 	else if (key == 's')
// 	{
// 		if (arr[info->y_player + 1][info->x_player] != 1){
// 			mlx_put_image_to_window(info->mlx, info->win, info->img_floor, info->x_player*64, info->y_player*64);
// 			info->y_player++;
// 			mlx_put_image_to_window(info->mlx, info->win, info->img_player, info->x_player*64, info->y_player*64);
// 		}
// 	}
// 	return 0;
// }