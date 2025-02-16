/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:17:54 by kuehara           #+#    #+#             */
/*   Updated: 2025/02/16 12:58:39 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_collision(t_game *game, float new_x, float new_y)
{
	int	tile_x;
	int	tile_y;
	int	col_count;

	tile_x = (int)roundf(new_x);
	tile_y = (int)roundf(new_y);
	col_count = 0;
	if (tile_x < 0 || tile_y < 0)
		return (0);
	if (game->map[tile_y] == NULL)
		return (0);
	while (game->map[tile_y][col_count] != INT_MIN)
		col_count++;
	if (tile_x >= col_count)
		return (0);
	if (game->map[tile_y][tile_x] == 1)
		return (0);
	return (1);
}

static void	update_position(float *x, float *y, int keycode, float speed)
{
	if (keycode == W_KEY)
		*y -= speed;
	else if (keycode == S_KEY)
		*y += speed;
	else if (keycode == A_KEY)
		*x -= speed;
	else if (keycode == D_KEY)
		*x += speed;
}

void	player_move(t_game *game, int keycode)
{
	float	speed;
	float	new_x;
	float	new_y;

	speed = 0.5f;
	new_x = game->player.x_pos;
	new_y = game->player.y_pos;
	update_position(&new_x, &new_y, keycode, speed);
	if (keycode == LEFT_ARROW_KEY)
		game->player.orientation -= 5;
	else if (keycode == RIGHT_ARROW_KEY)
		game->player.orientation += 5;
	else if (check_collision(game, new_x, new_y))
	{
		game->player.x_pos = new_x;
		game->player.y_pos = new_y;
	}
}
