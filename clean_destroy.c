/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oobbad <oobbad@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:25:32 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 12:31:15 by oobbad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	destroy_imgs(t_data *data)
{
	if (data->ea)
		mlx_destroy_image(data->mlx, data->ea);
	if (data->we)
		mlx_destroy_image(data->mlx, data->we);
	if (data->so)
		mlx_destroy_image(data->mlx, data->so);
	if (data->no)
		mlx_destroy_image(data->mlx, data->no);
}

void	destroy_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img_p);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	free_destroy_all(t_data *data)
{
	free_all(data->map);
	destroy_imgs(data);
	destroy_window(data);
}
