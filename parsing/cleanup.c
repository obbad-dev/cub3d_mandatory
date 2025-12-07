/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:24:43 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:24:44 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_print_error(char *s)
{
	write(2, s, ft_strlen(s));
}

void	free_all(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i++;
	}
	if (map)
		free(map);
}

void	free_texture(t_textures *tex, char **content)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(tex[i].id);
		free(tex[i].path);
		i++;
	}
	free_all(content);
}
