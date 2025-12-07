/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:25:05 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:25:06 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	get_rgb(char *str)
{
	char	**split;
	int		flag;
	int		i;

	int r, g, b;
	split = ft_split(str, ',');
	flag = 1;
	if (!split)
		return (-2);
	r = ft_atoi(split[0], &flag);
	g = ft_atoi(split[1], &flag);
	b = ft_atoi(split[2], &flag);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	if (!flag || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-2);
	else
		return ((r << 16) + (g << 8) + b);
}

int	handle_colors(char *line, int j, t_data *data)
{
	if (line[j] == 'F' && ft_isspace(line[j + 1]) && data->color_f == -1)
	{
		j++;
		skip_spaces(line, &j);
		data->color_f = get_rgb(line + j);
		return (1);
	}
	if (line[j] == 'C' && ft_isspace(line[j + 1]) && data->color_c == -1)
	{
		j++;
		skip_spaces(line, &j);
		data->color_c = get_rgb(line + j);
		return (1);
	}
	return (0);
}
