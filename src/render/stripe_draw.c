/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripe_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:54:24 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/18 23:16:07 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_stripe_pixels(t_game *game,
			int *data, t_raycast *rc, t_stripe *s)
{
	int	y;
	int	d;
	int	x;

	x = rc->column_x;
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		d = (y * 256) - (game->window.height * 128) + (rc->line_height * 128);
		s->tex_y = ((d * s->tex->height) / rc->line_height) / 256;
		if (s->tex_y < 0)
			s->tex_y = 0;
		else if (s->tex_y >= s->tex->height)
			s->tex_y = s->tex->height - 1;
		s->tex_color = ((int *)s->tex->addr)
		[s->tex_y * s->tex->width + s->tex_x];
		data[y * game->window.width + x] = s->tex_color;
		y++;
	}
}

void	draw_stripe_wrapper(t_game *game,
		int *data, t_raycast *rc, t_raydata *rd)
{
	t_stripe	s;

	select_texture(game, rd, rc, &s);
	if (s.tex == NULL || s.tex->addr == NULL)
	{
		ft_putendl_fd("Error: Texture not loaded", 2);
		return ;
	}
	compute_tex_x(game, rd, rc, &s);
	adjust_draw_range(game, rc);
	draw_stripe_pixels(game, data, rc, &s);
}
