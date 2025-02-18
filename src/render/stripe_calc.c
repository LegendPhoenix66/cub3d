/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripe_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:54:18 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/18 23:41:29 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_stripe(t_game *game, t_raydata *rd, t_raycast *rc)
{
	float	perp;

	if (rc->side == 0)
	{
		perp = (((float)rc->map_x - game->player.x_pos)
				+ (1.0f - (float)rc->step_x) / 2.0f) / rd->ray_dir_x;
	}
	else
	{
		perp = (((float)rc->map_y - game->player.y_pos)
				+ (1.0f - (float)rc->step_y) / 2.0f) / rd->ray_dir_y;
	}
	rd->perp_wall_dist = perp;
	rc->line_height = (int)(game->window.height / perp);
	rc->draw_start = -rc->line_height / 2 + game->window.height / 2;
	rc->draw_end = rc->draw_start + rc->line_height;
}

void	select_texture(t_game *game, t_raydata *rd, t_raycast *rc,
	t_stripe *s)
{
	if (rc->side == 0)
	{
		if (rd->ray_dir_x > 0.0f)
			s->tex = game->west_texture;
		else
			s->tex = game->east_texture;
	}
	else
	{
		if (rd->ray_dir_y > 0.0f)
			s->tex = game->north_texture;
		else
			s->tex = game->south_texture;
	}
}

void	compute_tex_x(t_game *game, t_raydata *rd, t_raycast *rc,
	t_stripe *s)
{
	s->wall_x = 0.0f;
	if (rc->side == 0)
		s->wall_x = game->player.y_pos + rd->perp_wall_dist * rd->ray_dir_y;
	else
		s->wall_x = game->player.x_pos + rd->perp_wall_dist * rd->ray_dir_x;
	s->wall_x = s->wall_x - floor(s->wall_x);
	s->tex_x = (int)(s->wall_x * s->tex->width);
	if (rc->side == 0)
	{
		if (rd->ray_dir_x > 0.0f)
			s->tex_x = s->tex->width - s->tex_x - 1;
	}
	else
	{
		if (rd->ray_dir_y < 0.0f)
			s->tex_x = s->tex->width - s->tex_x - 1;
	}
}

void	adjust_draw_range(t_game *game, t_raycast *rc)
{
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	if (rc->draw_end >= game->window.height)
		rc->draw_end = game->window.height - 1;
}
