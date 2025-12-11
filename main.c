/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:25:56 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/08 12:05:18 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_textures(t_textures *tex, t_data *data)
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

void	check_extension_file(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 5 || ft_strcmp(file + len - 4, ".cub"))
	{
		ft_print_error("Error\nFile must end with .cub\n");
		exit(1);
	}
}

int	main(int ac, char *av[])
{
	int		size;
	t_data	data;
	char	**content;

	if (ac != 2)
		return (1);
	data.color_c = -1;
	data.color_f = -1;
	data.mini_map = FALSE;
	check_extension_file(av[1]);
	content = fill_content(av[1], &size);
	init_textures(data.tex, &data);
	extract_textures_colors(content, &data);
	parse_map(content, &data);
	draw_window(&data);
	return (0);
}
