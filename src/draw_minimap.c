/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:23:13 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/13 08:09:40 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_minimap(t_game *game, int **int_map)
{
	t_minimap m;

	m.cell_size = 10;

	m.i = 0;
	while (int_map[m.i] != NULL)
	{
		m.j = 0;
		while (int_map[m.i][m.j] != -1)
		{
			if (int_map[m.i][m.j] == 1)
				m.color = 0xFFFFFF;
			else
				m.color = 0xAAAAAA;
			{
				int y = 0;
				while (y < m.cell_size)
				{
					int x = 0;
					while (x < m.cell_size)
					{
						mlx_pixel_put(game->window.mlx, game->window.win,
							m.j * m.cell_size + x,
							m.i * m.cell_size + y,
							m.color);
						x++;
					}
					y++;
				}
			}
			m.j++;
		}
		m.i++;
	}
	m.px = (int)(game->player_x * m.cell_size);
	m.py = (int)(game->player_y * m.cell_size);

	m.dy = -4;
	while (m.dy <= 4)
	{
		m.dx = -4;
		while (m.dx <= 4)
		{
			mlx_pixel_put(game->window.mlx, game->window.win,
				m.px + m.dx, m.py + m.dy, 0xFF0000); //red
			m.dx++;
		}
		m.dy++;
	}
}
