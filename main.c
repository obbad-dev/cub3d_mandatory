#include "header.h"

int main()
{
	t_data data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "My First MLX Window");
	data.img_p = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.img_s = mlx_get_data_addr(data.img_p, &data.bpp, &data.size_line, &data.endian);
	data.px = WIN_WIDTH / 2;
	data.py = WIN_HEIGHT / 2;
	data.rotation_angle = M_PI /2;
	render(&data);
	mlx_hook(data.win,2, 1L<<0, mov_player, &data);
    mlx_loop(data.mlx); 
    return (0);
}
