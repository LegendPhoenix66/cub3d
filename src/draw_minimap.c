/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:23:13 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/13 21:17:53 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_one_cell(t_game *game, t_minimap *mini, int row, int col)
{
	int	x;
	int	y;

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

void	draw_map_cells(t_game *game, t_minimap *mini)
{
	int	row;
	int	col;

	row = 0;
	while (game->map[row] != NULL)
	{
		col = 0;
		while (game->map[row][col] != INT_MIN)
		{
			if (game->map[row][col] == 1)
				mini->color = 0xFFFFFF;
			else if (game->map[row][col] == 0)
				mini->color = 0xAAAAAA;
            else
                mini->color = 0x000000;
			fill_one_cell(game, mini, row, col);
			col++;
		}
		row++;
	}
}

void	draw_player(t_game *game, t_minimap *mini)
{
	int	px;
	int	py;

	mini->player_center_x = game->player.x_pos + 0.5f;
	mini->player_center_y = game->player.y_pos + 0.5f;
	px = (int)(mini->player_center_x * mini->cell_size);
	py = (int)(mini->player_center_y * mini->cell_size);
	mini->offset_y = -4;
	while (mini->offset_y <= 4)
	{
		mini->offset_x = -4;
		while (mini->offset_x <= 4)
		{
			mlx_pixel_put(
				game->window.mlx,
				game->window.win,
				px + mini->offset_x,
				py + mini->offset_y,
				0xFF0000
				);
			mini->offset_x++;
		}
		mini->offset_y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_minimap	mini;

	mini.cell_size = 10;
	draw_map_cells(game, &mini);
	draw_player(game, &mini);
}
