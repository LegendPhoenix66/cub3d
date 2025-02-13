/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:58:40 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/13 00:08:00 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	esc_handler(int keycode, void *mlx)
{
	if (keycode == ESC_KEY)
	{
		#ifdef __linux__
			mlx_loop_end(mlx);
		#else
			mlx_destroy_window(mlx, ((t_game *)mlx)->window.win);
		#endif
		exit(0);
	}
	if (keycode == A_KEY)
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
		printf("Right Arrow\n");
	else
		printf("Unknown key: %d\n", keycode);
	return (0);
}
int close_window(void *param)
{ 
#ifdef __linux__
	t_game *game;

	game = (t_game *)param;
    mlx_loop_end(game->window.mlx);
    return (0);
#else
	(void) *param;
#endif
    exit(0);
    return (0);
}