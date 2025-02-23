/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:10:00 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/23 13:46:45 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_map_info(t_game *game, t_mapinfo *info)
{
	int		h;
	int		w;
	float	sx;
	float	sy;

	h = 0;
	while (game->map[h])
		h++;
	w = 0;
	while (game->map[0][w] != INT_MIN)
		w++;
	info->width = w;
	info->height = h;
	sx = (float)MINI_W / (float)w;
	sy = (float)MINI_H / (float)h;
	if (sx < sy)
		info->scale = sx;
	else
		info->scale = sy;
}

void	get_img_info(void *img, t_minimap *m)
{
	int		a;
	int		b;
	int		c;
	char	*data;

	data = mlx_get_data_addr(img, &a, &b, &c);
	m->img_data = data;
	m->img_size_line = b;
}

void	set_tile_color(t_minimap *m, int tile)
{
	if (tile == 1)
		m->color = 0x696969;
	else if (tile == 0)
		m->color = 0x3E1F0D;
	else
		m->color = 0x000000;
}
