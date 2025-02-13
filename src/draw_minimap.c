/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:23:13 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/13 08:36:00 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void fill_one_cell(t_game *game, t_minimap *mini, int row, int col)
{
	int x;
	int y;

	y = 0;
	while (y < mini->cell_size)
	{
		x = 0;
		while (x < mini->cell_size)
		{
			mlx_pixel_put(
				game->window.mlx,
				game->window.win,
				col * mini->cell_size + x,
				row * mini->cell_size + y,
				mini->color
			);
			x++;
		}
		y++;
	}
}

void draw_map_cells(t_game *game, int **int_map, t_minimap *mini)
{
	int row;
	int col;

	row = 0;
	while (int_map[row] != NULL)
	{
		col = 0;
		while (int_map[row][col] != -1)
		{
			if (int_map[row][col] == 1)
				mini->color = 0xFFFFFF;
			else
				mini->color = 0xAAAAAA;
			fill_one_cell(game, mini, row, col);
			col++;
		}
		row++;
	}
}

void draw_player(t_game *game, t_minimap *mini)
{
	int px;
	int py;
	int off_x;
	int off_y;

	px = (int)(game->player.x_pos * mini->cell_size);
	py = (int)(game->player.y_pos * mini->cell_size);
	off_y = -4;
	while (off_y <= 4)
	{
		off_x = -4;
		while (off_x <= 4)
		{
			mlx_pixel_put(
				game->window.mlx,
				game->window.win,
				px + off_x,
				py + off_y,
				0xFF0000
			);
			off_x++;
		}
		off_y++;
	}
}

void draw_minimap(t_game *game, int **int_map)
{
	t_minimap mini;

	mini.cell_size = 10;
	draw_map_cells(game, int_map, &mini);
	draw_player(game, &mini);
}
