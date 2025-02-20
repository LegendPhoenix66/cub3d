/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:58:40 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/20 17:41:30 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_handler(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == W_KEY)
		game->keys.w = 1;
	else if (keycode == A_KEY)
		game->keys.a = 1;
	else if (keycode == S_KEY)
		game->keys.s = 1;
	else if (keycode == D_KEY)
		game->keys.d = 1;
	else if (keycode == LEFT_ARROW_KEY)
		game->keys.left = 1;
	else if (keycode == RIGHT_ARROW_KEY)
		game->keys.right = 1;
	else if (keycode == ESC_KEY)
	{
#ifdef __linux__
		mlx_loop_end(game->window.mlx);
#else
		mlx_destroy_window(game->window.mlx, game->window.win);
		exit(0);
#endif
	}
	return (0);
}

int	key_release_handler(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == W_KEY)
		game->keys.w = 0;
	else if (keycode == A_KEY)
		game->keys.a = 0;
	else if (keycode == S_KEY)
		game->keys.s = 0;
	else if (keycode == D_KEY)
		game->keys.d = 0;
	else if (keycode == LEFT_ARROW_KEY)
		game->keys.left = 0;
	else if (keycode == RIGHT_ARROW_KEY)
		game->keys.right = 0;
	return (0);
}

int	close_window(void *param)
{
	t_game	*game;

#ifdef __linux__
	game = (t_game *)param;
	mlx_loop_end(game->window.mlx);
	return (0);
#else
	(void)*param;
#endif
	exit(0);
	return (0);
}
