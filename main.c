#include "header.h"

void init_textures(t_textures *tex, t_data *data)
{
	tex[0].id = NULL;
	tex[0].path = NULL;
	tex[1].id = NULL;
	tex[1].path = NULL;
	tex[2].id = NULL;
	tex[2].path = NULL;
	tex[3].id = NULL;
	tex[3].path = NULL;
	data->no = NULL;
	data->we = NULL;
	data->so = NULL;
	data->ea = NULL;
}

int main(int ac, char *av[])
{
	int size;
	t_data data;
	char **content ;

	if (ac != 2)
		return 1;
	data.color_c = -1;
	data.color_f = -1;
	content = fill_content(av[1], &size);
	init_textures(data.tex, &data);
	extract_textures_colors(content, &data);
	parse_map(content, &data);
	draw_window(&data);
    return (0);
}
