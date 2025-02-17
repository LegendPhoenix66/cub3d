/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:58:40 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/17 11:07:15 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	esc_handler(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == ESC_KEY)
	{
		#ifdef __linux__
		mlx_loop_end(game->window.mlx);
		#else
		mlx_destroy_window(game->window.mlx, game->window.win);
		#endif
		exit(0);
	}
/* 	if (keycode == A_KEY)
		printf("A\n");
	else if (keycode == W_KEY)
		printf("W\n");
	else if (keycode == S_KEY)
		printf("S\n");
	else if (keycode == D_KEY)
		printf("D\n");
	else if (keycode == LEFT_ARROW_KEY)
		printf("Left Arrow\n");
	else if (keycode == RIGHT_ARROW_KEY)
		printf("Right Arrow\n"); */
	else if (keycode == A_KEY || keycode == W_KEY
		|| keycode == S_KEY || keycode == D_KEY
		|| keycode == LEFT_ARROW_KEY || keycode == RIGHT_ARROW_KEY)
	{
		player_move(game, keycode);
		render_3d(game);
		draw_minimap(game);
	}
	else
		printf("Unknown key: %d\n", keycode);
	return (0);
}

int	close_window(void *param)
{
#ifdef __linux__
	t_game	*game;

	game = (t_game *)param;
	mlx_loop_end(game->window.mlx);
	return (0);
#else
	(void) *param;
#endif
	exit(0);
	return (0);
}
