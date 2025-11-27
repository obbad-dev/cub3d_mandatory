#include "../header.h"

void ft_print_error(char *s)
{
	write(2, s, ft_strlen(s));
}
void free_all(char **map)
{
	int i;

	i = 0;
	while (map && map[i])
	{
		free (map[i]);
		i++;
	}
	if (map)
		free(map);
}

void free_texture(t_textures *tex, char **content)
{
	int i;

	i = 0;
	while (i < 4)
	{
		free(tex[i].id);
		free(tex[i].path);
		i++;
	}
	free_all(content);
}

