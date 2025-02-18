/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_tiles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:15:00 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/18 01:36:35 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_img(t_minimap *m, int x, int y, int color)
{
	int	offset;

	offset = (y * m->img_size_line) + (x * 4);
	m->img_data[offset] = color & 0xFF;
	m->img_data[offset + 1] = (color >> 8) & 0xFF;
	m->img_data[offset + 2] = (color >> 16) & 0xFF;
	m->img_data[offset + 3] = 0;
}

void	get_tile_area(t_mapinfo *info, t_draw_map *d, t_area *area)
{
	d->start_x = (int)(d->col * info->scale);
	d->start_y = (int)(d->row * info->scale);
	d->end_x = (int)((d->col + 1) * info->scale);
	d->end_y = (int)((d->row + 1) * info->scale);
	area->sx = d->start_x;
	area->sy = d->start_y;
	area->ex = d->end_x;
	area->ey = d->end_y;
}

void	fill_tile_area(t_minimap *m, t_area area)
{
	int	y;
	int	x;

	y = area.sy;
	while (y < area.ey)
	{
		x = area.sx;
		while (x < area.ex)
		{
			if (x >= 0 && x < MINIMAP_WIDTH && y >= 0 && y < MINIMAP_HEIGHT)
				put_pixel_to_img(m, x, y, m->color);
			x++;
		}
		y++;
	}
}

void	draw_map_scaled(t_game *game, t_minimap *m, t_mapinfo *info)
{
	t_draw_map	d;
	t_area		area;

	d.row = 0;
	while (d.row < info->height)
	{
		d.col = 0;
		while (d.col < info->width)
		{
			d.tile = game->map[d.row][d.col];
			if (d.tile == INT_MIN)
				break ;
			set_tile_color(m, d.tile);
			get_tile_area(info, &d, &area);
			fill_tile_area(m, area);
			d.col++;
		}
		d.row++;
	}
}
