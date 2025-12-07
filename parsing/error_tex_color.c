/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tex_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:24:46 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:24:47 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

bool	check_parse_textures_is_valide(t_textures *tex, t_data *data)
{
	int	i;
	int	w;
	int	h;

	i = 0;
	while (i < 4)
	{
		if (!ft_strcmp(tex[i].id, "NO"))
			data->no = mlx_xpm_file_to_image(data->mlx, tex[i].path, &w, &h);
		else if (!ft_strcmp(tex[i].id, "SO"))
			data->so = mlx_xpm_file_to_image(data->mlx, tex[i].path, &w, &h);
		else if (!ft_strcmp(tex[i].id, "WE"))
			data->we = mlx_xpm_file_to_image(data->mlx, tex[i].path, &w, &h);
		else if (!ft_strcmp(tex[i].id, "EA"))
			data->ea = mlx_xpm_file_to_image(data->mlx, tex[i].path, &w, &h);
		i++;
	}
	if (!data->no || !data->so || !data->we || !data->ea)
		return (false);
	free_texture(data->tex, NULL);
	return (true);
}

void	validate_textures(t_data *data, char **content, int k)
{
	if (k != 4)
	{
		ft_print_error("Error\nMissing one texture identifiers\n");
		free_texture(data->tex, content);
		exit(1);
	}
	if (check_if_malloc_fail(data->tex))
	{
		ft_print_error("malloc fail in textures\n");
		free_texture(data->tex, content);
		exit(1);
	}
}

void	validate_colors(t_data *data, char **content)
{
	if (data->color_f <= -1 || data->color_c <= -1)
	{
		ft_print_error("Error\nCheck colors\n");
		free_texture(data->tex, content);
		exit(1);
	}
}
