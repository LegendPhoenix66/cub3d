/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:23:13 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/13 01:18:14 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_minimap(t_game *game, int **int_map, double player_x, double player_y)
{
	int i;
	int j;
	int cell_size;
	int color;
	int px;
	int py;

	cell_size = 10;
	i = 0;
	while (int_map[i] != NULL)
	{
		j = 0;
		while (int_map[i][j] != -1)
		{
			if (int_map[i][j] == 1)
				color = 0xFFFFFF;  // white
			else
				color = 0xAAAAAA;  // grey
			{
				int y = 0;
				while (y < cell_size)
				{
					int x = 0;
					while (x < cell_size)
					{
						mlx_pixel_put(game->window.mlx, game->window.win,
							j * cell_size + x, i * cell_size + y, color);
						x++;
					}
					y++;
				}
			}
			j++;
		}
		i++;
	}
	px = (int)(player_x * cell_size);
	py = (int)(player_y * cell_size);
	{
		int dy = -4;
		while (dy <= 4)
		{
			int dx = -4;
			while (dx <= 4)
			{
				mlx_pixel_put(game->window.mlx, game->window.win,
					px + dx, py + dy, 0xFF0000); // red
				dx++;
			}
			dy++;
		}
	}
}
