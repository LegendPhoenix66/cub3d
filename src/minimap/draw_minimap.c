/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:06:13 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/23 13:46:37 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_player_scaled(t_game *game, t_minimap *m, float scale)
{
	t_player_draw	p;

	p.player_x = (int)((game->player.x_pos) * scale);
	p.player_y = (int)((game->player.y_pos) * scale);
	p.size = 1;
	p.offset_y = -p.size;
	while (p.offset_y <= p.size)
	{
		p.offset_x = -p.size;
		while (p.offset_x <= p.size)
		{
			p.render_x = p.player_x + p.offset_x;
			p.render_y = p.player_y + p.offset_y;
			if (p.render_x >= 0 && p.render_x < MINI_W
				&& p.render_y >= 0 && p.render_y < MINI_H)
				put_pixel_to_img(m, p.render_x, p.render_y, 0xFF0000);
			p.offset_x++;
		}
		p.offset_y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_minimap	bg;
	t_minimap	active;
	t_mapinfo	map_info;

	get_map_info(game, &map_info);
	get_img_info(game->minimap_bg->img, &bg);
	get_img_info(game->minimap_image->img, &active);
	ft_memcpy(active.img_data, bg.img_data,
		MINI_H * active.img_size_line);
	draw_player_scaled(game, &active, map_info.scale);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->minimap_image->img, MINIMAP_POS_X, MINIMAP_POS_Y);
}
