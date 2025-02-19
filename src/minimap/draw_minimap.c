/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:06:13 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/19 21:44:27 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_player_scaled(t_game *game, t_minimap *m, float scale)
{
	t_player_draw	p;

	p.player_x = (int)((game->player.x_pos + 0.5f) * scale);
	p.player_y = (int)((game->player.y_pos + 0.5f) * scale);
	p.size = 2;
	p.offset_y = -p.size;
	while (p.offset_y <= p.size)
	{
		p.offset_x = -p.size;
		while (p.offset_x <= p.size)
		{
			p.render_x = p.player_x + p.offset_x;
			p.render_y = p.player_y + p.offset_y;
			if (p.render_x >= 0 && p.render_x < MINIMAP_WIDTH
				&& p.render_y >= 0 && p.render_y < MINIMAP_HEIGHT)
				put_pixel_to_img(m, p.render_x, p.render_y, 0xFF0000);
			p.offset_x++;
		}
		p.offset_y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_mapinfo	map_info;
	t_minimap	m;

	get_map_info(game, &map_info);
	if (!game->minimap_image)
	{
		game->minimap_image = gc_malloc(sizeof(t_image));
		game->minimap_image->img = mlx_new_image(game->window.mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	}
	get_img_info(game->minimap_image->img, &m);
	draw_map_scaled(game, &m, &map_info);
	draw_player_scaled(game, &m, map_info.scale);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->minimap_image->img, MINIMAP_POS_X, MINIMAP_POS_Y);
}

