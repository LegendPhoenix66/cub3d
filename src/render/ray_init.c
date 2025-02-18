/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:52:15 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/18 23:19:13 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray_direction(t_game *game, int x, t_raydata *rd,
	t_raycast *rc)
{
	t_rayinit	ray;

	ray.angle = game->player.orientation * (M_PI / 180.0f);
	ray.camera = (2.0f * x / (float)game->window.width) - 1.0f;
	ray.dir_x = sin(ray.angle);
	ray.dir_y = -cos(ray.angle);
	ray.plane_x = 0.66f * cos(ray.angle);
	ray.plane_y = 0.66f * sin(ray.angle);
	rd->ray_dir_x = ray.dir_x + ray.plane_x * ray.camera;
	rd->ray_dir_y = ray.dir_y + ray.plane_y * ray.camera;
	rc->map_x = (int)game->player.x_pos;
	rc->map_y = (int)game->player.y_pos;
	if (rd->ray_dir_x == 0.0f)
		rd->delta_dist_x = 1e30f;
	else
		rd->delta_dist_x = fabs(1.0f / rd->ray_dir_x);
	if (rd->ray_dir_y == 0.0f)
		rd->delta_dist_y = 1e30f;
	else
		rd->delta_dist_y = fabs(1.0f / rd->ray_dir_y);
}

void	init_ray_steps(t_game *game, t_raydata *rd, t_raycast *rc)
{
	if (rd->ray_dir_x < 0.0f)
		rc->step_x = -1;
	else
		rc->step_x = 1;
	if (rd->ray_dir_x < 0.0f)
		rd->side_dist_x = (game->player.x_pos - (float)rc->map_x)
			* rd->delta_dist_x;
	else
		rd->side_dist_x = (((float)rc->map_x + 1.0f) - game->player.x_pos)
			* rd->delta_dist_x;
	if (rd->ray_dir_y < 0.0f)
		rc->step_y = -1;
	else
		rc->step_y = 1;
	if (rd->ray_dir_y < 0.0f)
		rd->side_dist_y = (game->player.y_pos - (float)rc->map_y)
			* rd->delta_dist_y;
	else
		rd->side_dist_y = (((float)rc->map_y + 1.0f) - game->player.y_pos)
			* rd->delta_dist_y;
	rc->side = -1;
}

static int	check_hit(t_game *game, t_raycast *rc)
{
	if (rc->map_x < 0 || rc->map_y < 0)
		return (1);
	if (game->map[rc->map_y] == NULL)
		return (1);
	if (game->map[rc->map_y][rc->map_x] == INT_MIN)
		return (1);
	if (game->map[rc->map_y][rc->map_x] == 1)
		return (1);
	return (0);
}

void	perform_dda(t_game *game, t_raydata *rd, t_raycast *rc)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (rd->side_dist_x < rd->side_dist_y)
		{
			rd->side_dist_x = rd->side_dist_x + rd->delta_dist_x;
			rc->map_x = rc->map_x + rc->step_x;
			rc->side = 0;
		}
		else
		{
			rd->side_dist_y = rd->side_dist_y + rd->delta_dist_y;
			rc->map_y = rc->map_y + rc->step_y;
			rc->side = 1;
		}
		hit = check_hit(game, rc);
	}
}
