/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:25:01 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:25:02 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	handle_no_texture(char *line, int j, t_data *data, int *k)
{
	if (line[j] == 'N' && line[j + 1] == 'O' && ft_isspace(line[j + 2])
		&& !check_if_double_id(data->tex, "NO"))
	{
		j += 2;
		skip_spaces(line, &j);
		data->tex[*k].id = ft_strdup("NO");
		data->tex[*k].path = ft_strdup(line + j);
		(*k)++;
		return (1);
	}
	return (0);
}

int	handle_so_texture(char *line, int j, t_data *data, int *k)
{
	if (line[j] == 'S' && line[j + 1] == 'O' && ft_isspace(line[j + 2])
		&& !check_if_double_id(data->tex, "SO"))
	{
		j += 2;
		skip_spaces(line, &j);
		data->tex[*k].id = ft_strdup("SO");
		data->tex[*k].path = ft_strdup(line + j);
		(*k)++;
		return (1);
	}
	return (0);
}

int	handle_we_texture(char *line, int j, t_data *data, int *k)
{
	if (line[j] == 'W' && line[j + 1] == 'E' && ft_isspace(line[j + 2])
		&& !check_if_double_id(data->tex, "WE"))
	{
		j += 2;
		skip_spaces(line, &j);
		data->tex[*k].id = ft_strdup("WE");
		data->tex[*k].path = ft_strdup(line + j);
		(*k)++;
		return (1);
	}
	return (0);
}

int	handle_ea_texture(char *line, int j, t_data *data, int *k)
{
	if (line[j] == 'E' && line[j + 1] == 'A' && ft_isspace(line[j + 2])
		&& !check_if_double_id(data->tex, "EA"))
	{
		j += 2;
		skip_spaces(line, &j);
		data->tex[*k].id = ft_strdup("EA");
		data->tex[*k].path = ft_strdup(line + j);
		(*k)++;
		return (1);
	}
	return (0);
}

int	handle_textures(char *line, int j, t_data *data, int *k)
{
	if (handle_no_texture(line, j, data, k))
		return (1);
	if (handle_so_texture(line, j, data, k))
		return (1);
	if (handle_we_texture(line, j, data, k))
		return (1);
	if (handle_ea_texture(line, j, data, k))
		return (1);
	return (0);
}