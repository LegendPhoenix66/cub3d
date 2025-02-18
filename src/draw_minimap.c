/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:06:13 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/18 15:02:54 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player_scaled(t_game *game, t_minimap *m, float scale)
{
	t_player_draw	p;

	p.px = (int)((game->player.x_pos + 0.5f) * scale);
	p.py = (int)((game->player.y_pos + 0.5f) * scale);
	p.size = 2;
	p.dy = -p.size;
	while (p.dy <= p.size)
	{
		p.dx = -p.size;
		while (p.dx <= p.size)
		{
			p.rx = p.px + p.dx;
			p.ry = p.py + p.dy;
			if (p.rx >= 0 && p.rx < MINIMAP_WIDTH
				&& p.ry >= 0 && p.ry < MINIMAP_HEIGHT)
				put_pixel_to_img(m, p.rx, p.ry, 0xFF0000);
			p.dx++;
		}
		p.dy++;
	}
}

void	draw_minimap(t_game *game)
{
	t_mapinfo	map_info;
	t_minimap	m;
	void		*img;

	get_map_info(game, &map_info);
	img = mlx_new_image(game->window.mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	get_img_info(img, &m);
	draw_map_scaled(game, &m, &map_info);
	draw_player_scaled(game, &m, map_info.scale);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		img, MINIMAP_POS_X, MINIMAP_POS_Y);
	mlx_destroy_image(game->window.mlx, img);
}
