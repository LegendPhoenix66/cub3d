/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:17:54 by kuehara           #+#    #+#             */
/*   Updated: 2025/02/19 21:36:15 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static int	check_collision(t_game *game, float new_x, float new_y)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)new_x;
	tile_y = (int)new_y;
	if (tile_x < 0 || tile_y < 0)
		return (0);
	if (game->map[tile_y] == NULL)
		return (0);
	if (game->map[tile_y][tile_x] == INT_MIN)
		return (0);
	if (game->map[tile_y][tile_x] == 1)
		return (0);
	return (1);
}


static void	update_position(float *x, float *y, int keycode, float speed, float angle)
{
	if (keycode == W_KEY)
	{
		*x = *x + sin(angle) * speed;
		*y = *y - cos(angle) * speed;
	}
	else if (keycode == S_KEY)
	{
		*x = *x - sin(angle) * speed;
		*y = *y + cos(angle) * speed;
	}
	else if (keycode == A_KEY)
	{
		*x = *x - cos(angle) * speed;
		*y = *y - sin(angle) * speed;
	}
	else if (keycode == D_KEY)
	{
		*x = *x + cos(angle) * speed;
		*y = *y + sin(angle) * speed;
	}
}

void	player_move(t_game *game, int keycode)
{
	float	speed;
	float	angle;
	float	new_x;
	float	new_y;

	speed = 0.2f;
	new_x = game->player.x_pos;
	new_y = game->player.y_pos;
	angle = game->player.orientation * (M_PI / 180.0f);
	update_position(&new_x, &new_y, keycode, speed, angle);
	if (keycode == LEFT_ARROW_KEY)
	{
		game->player.orientation -= 5;
		if (game->player.orientation < 0)
			game->player.orientation += 360;
	}
	else if (keycode == RIGHT_ARROW_KEY)
	{
		game->player.orientation += 5;
		if (game->player.orientation >= 360)
			game->player.orientation -= 360;
	}
	else if (check_collision(game, new_x, new_y))
	{
		game->player.x_pos = new_x;
		game->player.y_pos = new_y;
	}
}

