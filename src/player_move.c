/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:17:54 by kuehara           #+#    #+#             */
/*   Updated: 2025/02/23 13:07:14 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	compute_offset(t_player *player, int keycode, float *dx, float *dy)
{
	float	angle;
	float	speed;

	angle = player->orientation * (M_PI / 180.0f);
	speed = 0.05f;
	if (keycode == W_KEY)
	{
		*dx = sin(angle) * speed;
		*dy = -cos(angle) * speed;
	}
	else if (keycode == S_KEY)
	{
		*dx = -sin(angle) * speed;
		*dy = cos(angle) * speed;
	}
	else if (keycode == A_KEY)
	{
		*dx = sin(angle - M_PI_2) * speed;
		*dy = -cos(angle - M_PI_2) * speed;
	}
	else if (keycode == D_KEY)
	{
		*dx = sin(angle + M_PI_2) * speed;
		*dy = -cos(angle + M_PI_2) * speed;
	}
}

static void	move_player(t_game *game, int keycode)
{
	float	dx;
	float	dy;
	float	new_x;
	float	new_y;

	compute_offset(&game->player, keycode, &dx, &dy);
	new_x = game->player.x_pos + dx;
	new_y = game->player.y_pos + dy;
	if (check_collision(game, new_x, game->player.y_pos))
		game->player.x_pos = new_x;
	if (check_collision(game, game->player.x_pos, new_y))
		game->player.y_pos = new_y;
}

void	player_move(t_game *game, int keycode)
{
	if (keycode == LEFT_ARROW_KEY || keycode == RIGHT_ARROW_KEY)
	{
		if (keycode == LEFT_ARROW_KEY)
			game->player.orientation -= 2;
		else if (keycode == RIGHT_ARROW_KEY)
			game->player.orientation += 2;
		if (game->player.orientation < 0)
			game->player.orientation += 360;
		if (game->player.orientation >= 360)
			game->player.orientation -= 360;
	}
	else
		move_player(game, keycode);
}
