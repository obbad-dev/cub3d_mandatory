/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakbour <kakbour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:26:01 by oobbad            #+#    #+#             */
/*   Updated: 2025/12/07 17:10:31 by kakbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	check_wall(char **map, double x, double y, int rows)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_y >= rows
		|| map_x >= (int)ft_strlen(map[map_y]))
		return (true);
	return (map[map_y][map_x] != '0');
}

int	key_press(t_key key, t_keys *keys)
{
	if (key == KYS_A)
		keys->kys_a = TRUE;
	else if (key == KYS_D)
		keys->kys_d = TRUE;
	else if (key == KYS_S)
		keys->kys_s = TRUE;
	else if (key == KYS_W)
		keys->kys_w = TRUE;
	else if (key == KYS_LEFT)
		keys->kys_left = TRUE;
	else if (key == KYS_RIGHT)
		keys->kys_right = TRUE;
	else if (key == k_ESC)
		keys->kys_esc = TRUE;
	return (0);
}

int	key_release(t_key key, t_keys *keys)
{
	if (key == KYS_A)
		keys->kys_a = FALSE;
	else if (key == KYS_D)
		keys->kys_d = FALSE;
	else if (key == KYS_S)
		keys->kys_s = FALSE;
	else if (key == KYS_W)
		keys->kys_w = FALSE;
	else if (key == KYS_LEFT)
		keys->kys_left = FALSE;
	else if (key == KYS_RIGHT)
		keys->kys_right = FALSE;
	else if (key == k_ESC)
		keys->kys_esc = FALSE;
	return (0);
}

void	move(double *x, double *y, t_data *data, t_move move_direction)
{
	data->turn_on = 1;
	if (move_direction == MOVE_UP)
	{
		*x = data->px + cos(data->angle_direction) * MOVE_SPEED;
		*y = data->py + sin(data->angle_direction) * MOVE_SPEED;
	}
	else if (move_direction == MOVE_DOWN)
	{
		*x = data->px - cos(data->angle_direction) * MOVE_SPEED;
		*y = data->py - sin(data->angle_direction) * MOVE_SPEED;
	}
	else if (move_direction == MOVE_LEFT)
	{
		*x = data->px - cos(data->angle_direction + M_PI / 2) * MOVE_SPEED;
		*y = data->py - sin(data->angle_direction + M_PI / 2) * MOVE_SPEED;
	}
	else if (move_direction == MOVE_RIGHT)
	{
		*x = data->px + cos(data->angle_direction + M_PI / 2) * MOVE_SPEED;
		*y = data->py + sin(data->angle_direction + M_PI / 2) * MOVE_SPEED;
	}
}

bool	check_outofmap(char **map, double x, double y, int rows)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_y >= rows
		|| map_x >= (int)ft_strlen(map[map_y]))
		return (true);
	return false;
}

void	mov_player(t_data *data)
{
	double	x;
	double	y;

	x = 0;
	y = 0;
	data->turn_on = 0;
	if (data->keys.kys_a)
		move(&x, &y, data, MOVE_LEFT);
	if (data->keys.kys_d)
		move(&x, &y, data, MOVE_RIGHT);
	if (data->keys.kys_w)
		move(&x, &y, data, MOVE_UP);
	if (data->keys.kys_s)
		move(&x, &y, data, MOVE_DOWN);
	if (data->keys.kys_left)
		data->angle_direction -= ROTATION_SPEED;
	if (data->keys.kys_right)
		data->angle_direction += ROTATION_SPEED;
	if (data->keys.kys_esc)
		exit((free_destroy_all(data), 0));
	if (data->turn_on && !check_outofmap(data->map, x, y, data->rows))
	{
		data->px = x;
		data->py = y;
	}
}
