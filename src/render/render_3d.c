/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:12:11 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/19 00:02:00 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_floor_and_ceiling(t_game *game, int *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->window.height / 2)
	{
		x = 0;
		while (x < game->window.width)
		{
			data[y * game->window.width + x] = game->ceiling_color;
			x++;
		}
		y++;
	}
	y = game->window.height / 2;
	while (y < game->window.height)
	{
		x = 0;
		while (x < game->window.width)
		{
			data[y * game->window.width + x] = game->floor_color;
			x++;
		}
		y++;
	}
}

static void	raycast_column(t_game *game, int x, int *data)
{
	t_raydata	rd;
	t_raycast	rc;

	ft_bzero(&rc, sizeof(t_raycast));
	rc.column_x = x;
	init_ray_direction(game, x, &rd, &rc);
	init_ray_steps(game, &rd, &rc);
	perform_dda(game, &rd, &rc);
	calculate_stripe(game, &rd, &rc);
	draw_stripe_wrapper(game, data, &rc, &rd);
}

void	render_3d(t_game *game)
{
	t_image	img;
	int		*data;
	int		x;

	img.img = mlx_new_image(game->window.mlx,
			game->window.width, game->window.height);
	data = (int *)mlx_get_data_addr(img.img, &img.bpp,
			&img.line_length, &img.endian);
	draw_floor_and_ceiling(game, data);
	x = 0;
	while (x < game->window.width)
	{
		raycast_column(game, x, data);
		x++;
	}
	mlx_put_image_to_window(game->window.mlx, game->window.win, img.img, 0, 0);
	mlx_destroy_image(game->window.mlx, img.img);
}


