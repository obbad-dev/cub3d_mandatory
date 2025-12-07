/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_color_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:24:54 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:24:55 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	skip_spaces(char *line, int *j)
{
	while (line && line[*j])
	{
		if ((line[*j] >= 9 && line[*j] <= 13) || line[*j] == 32)
			(*j)++;
		else
			break ;
	}
}

int	process_line(char *line, t_data *data, int *k, int *begin_map)
{
	int	j;

	j = 0;
	skip_spaces(line, &j);
	if (line[j] == '\0')
		return (0);
	if (handle_textures(line, j, data, k))
		return (0);
	if (handle_colors(line, j, data))
		return (0);
	if (!check_line_is_one(line + j, begin_map))
	{
		return (1);
	}
	return (0);
}

void	extract_textures_colors(char **content, t_data *data)
{
	int	i;
	int	k;
	int	begin_map;

	i = 0;
	k = 0;
	begin_map = 0;
	while (content && content[i] && !begin_map)
	{
		if (process_line(content[i], data, &k, &begin_map))
		{
			ft_print_error("Error\nLine invalid\n");
			free_texture(data->tex, content);
			exit(1);
		}
		i++;
	}
	data->begin_map = i - 1;
	validate_textures(data, content, k);
	validate_colors(data, content);
}
