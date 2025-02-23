/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composite_frame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:34:08 by kuehara           #+#    #+#             */
/*   Updated: 2025/02/23 13:38:30 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_real_minimap_size(t_mapinfo *info, int *real_w, int *real_h)
{
	*real_w = (int)(info->width * info->scale);
	*real_h = (int)(info->height * info->scale);
}

static void	copy_bg_draw_player(t_game *game, t_minimap *bg, t_minimap *active)
{
	t_mapinfo	map_info;
	int			real_w;
	int			real_h;
	int			y;

	get_map_info(game, &map_info);
	get_real_minimap_size(&map_info, &real_w, &real_h);
	y = 0;
	while (y < real_h)
	{
		ft_memcpy(active->img_data + y * active->img_size_line,
			bg->img_data + y * bg->img_size_line, real_w * 4);
		y++;
	}
	draw_player_scaled(game, active, map_info.scale);
}

static void	blit_minimap_to_render(t_game *game, t_minimap *active)
{
	t_mapinfo	map_info;
	int			real_w;
	int			real_h;
	t_blit		b;

	get_map_info(game, &map_info);
	get_real_minimap_size(&map_info, &real_w, &real_h);
	b.render_data = game->render_image->addr;
	b.render_line = game->render_image->line_length;
	b.bytes_per_row = real_w * 4;
	b.y = 0;
	while (b.y < real_h)
	{
		b.src_offset = b.y * active->img_size_line;
		b.dest_offset = ((MINIMAP_POS_Y + b.y) * b.render_line)
			+ (MINIMAP_POS_X * 4);
		ft_memcpy(b.render_data + b.dest_offset,
			active->img_data + b.src_offset, b.bytes_per_row);
		b.y++;
	}
}

void	composite_minimap_on_render(t_game *game)
{
	t_minimap	bg;
	t_minimap	active;

	get_img_info(game->minimap_bg->img, &bg);
	get_img_info(game->minimap_image->img, &active);
	copy_bg_draw_player(game, &bg, &active);
	blit_minimap_to_render(game, &active);
}

void	composite_frame(t_game *game)
{
	int	*data;
	int	x;

	data = (int *)mlx_get_data_addr(game->render_image->img,
			&game->render_image->bpp, &game->render_image->line_length,
			&game->render_image->endian);
	game->render_image->addr = mlx_get_data_addr(game->render_image->img,
			&game->render_image->bpp, &game->render_image->line_length,
			&game->render_image->endian);
	draw_floor_and_ceiling(game, data);
	x = 0;
	while (x < game->window.width)
	{
		raycast_column(game, x, data);
		x++;
	}
	composite_minimap_on_render(game);
}
