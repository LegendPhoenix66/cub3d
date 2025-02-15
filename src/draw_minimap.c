/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:23:13 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/15 23:19:42 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel_to_img(t_minimap *m, int x, int y, int color)
{
	int	offset;

	offset = (y * m->img_size_line) + (x * 4);
	m->img_data[offset] = color & 0xFF;
	m->img_data[offset + 1] = (color >> 8) & 0xFF;
	m->img_data[offset + 2] = (color >> 16) & 0xFF;
	m->img_data[offset + 3] = 0;
}

static void	fill_cell(t_minimap *m, int row, int col)
{
	int	base_x;
	int	base_y;
	int	x;
	int	y;

	base_x = col * m->cell_size;
	base_y = row * m->cell_size;
	y = 0;
	while (y < m->cell_size)
	{
		x = 0;
		while (x < m->cell_size)
		{
			put_pixel_to_img(m, base_x + x, base_y + y, m->color);
			x++;
		}
		y++;
	}
}

static void	draw_map(t_game *game, t_minimap *m)
{
	int	row;
	int	col;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col] != INT_MIN)
		{
			if (game->map[row][col] == 1)
				m->color = 0x696969;
			else if (game->map[row][col] == 0)
				m->color = 0x3E1F0D;
			else
				m->color = 0x000000;
			fill_cell(m, row, col);
			col++;
		}
		row++;
	}
}

static void	draw_player(t_game *game, t_minimap *m)
{
	int	px;
	int	py;
	int	offset_x;
	int	offset_y;

	px = (int)((game->player.x_pos + 0.5f) * m->cell_size);
	py = (int)((game->player.y_pos + 0.5f) * m->cell_size);
	offset_y = -4;
	while (offset_y <= 4)
	{
		offset_x = -4;
		while (offset_x <= 4)
		{
			put_pixel_to_img(m, px + offset_x, py + offset_y, 0xFF0000);
			offset_x++;
		}
		offset_y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_minimap	m;
	int			info[3];
	void		*img;

	m.cell_size = 10;
	img = mlx_new_image(game->window.mlx,
			game->window.width,
			game->window.height);
	m.img_data = mlx_get_data_addr(img, &info[0], &info[1], &info[2]);
	m.img_size_line = info[1];
	draw_map(game, &m);
	draw_player(game, &m);
	mlx_put_image_to_window(game->window.mlx, game->window.win, img, 0, 0);
	mlx_destroy_image(game->window.mlx, img);
}
