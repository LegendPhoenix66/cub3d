/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:23:13 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/17 21:54:33 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void put_pixel_to_img(t_minimap *m, int x, int y, int color)
{
	int offset = (y * m->img_size_line) + (x * 4);
	m->img_data[offset]     =  color        & 0xFF;
	m->img_data[offset + 1] = (color >> 8)  & 0xFF;
	m->img_data[offset + 2] = (color >> 16) & 0xFF;
	m->img_data[offset + 3] = 0;
}

static void draw_map_scaled(t_game *game, t_minimap *m,
		float scale, int map_width, int map_height)
{
	for (int row = 0; row < map_height; row++)
	{
		for (int col = 0; col < map_width; col++)
		{
			int tile = game->map[row][col];
			if (tile == INT_MIN) 
				break;

			if (tile == 1)
				m->color = 0x696969; 
			else if (tile == 0)
				m->color = 0x3E1F0D; 
			else
				m->color = 0x000000;

			int start_x = (int)(col * scale);
			int start_y = (int)(row * scale);
			int end_x   = (int)((col + 1) * scale);
			int end_y   = (int)((row + 1) * scale);

			for (int y = start_y; y < end_y; y++)
			{
				for (int x = start_x; x < end_x; x++)
				{
					if (x >= 0 && x < MINIMAP_WIDTH && y >= 0 && y < MINIMAP_HEIGHT)
						put_pixel_to_img(m, x, y, m->color);
				}
			}
		}
	}
}

static void draw_player_scaled(t_game *game, t_minimap *m,
		float scale)
{
	int px = (int)((game->player.x_pos + 0.5f) * scale);
	int py = (int)((game->player.y_pos + 0.5f) * scale);
	int size = 2;

	for (int dy = -size; dy <= size; dy++)
	{
		for (int dx = -size; dx <= size; dx++)
		{
			int rx = px + dx;
			int ry = py + dy;
			if (rx >= 0 && rx < MINIMAP_WIDTH && ry >= 0 && ry < MINIMAP_HEIGHT)
				put_pixel_to_img(m, rx, ry, 0xFF0000);
		}
	}
}

void draw_minimap(t_game *game)
{
	t_minimap	m;
	int			info[3];
	void		*img;
	int			map_height = 0;
	int			map_width  = 0;

	while (game->map[map_height])
		map_height++;

	while (game->map[0][map_width] != INT_MIN)
		map_width++;

	float scale_x = (float)MINIMAP_WIDTH  / (float)map_width;
	float scale_y = (float)MINIMAP_HEIGHT / (float)map_height;
	float scale   = (scale_x < scale_y) ? scale_x : scale_y;

	img = mlx_new_image(game->window.mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);

	m.img_data = mlx_get_data_addr(img, &info[0], &info[1], &info[2]);
	m.img_size_line = info[1];

	draw_map_scaled(game, &m, scale, map_width, map_height);

	draw_player_scaled(game, &m, scale);

	mlx_put_image_to_window(game->window.mlx, game->window.win, img, MINIMAP_POS_X, MINIMAP_POS_Y);
	mlx_destroy_image(game->window.mlx, img);
}
