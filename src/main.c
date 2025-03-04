/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:05:41 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 16:39:19 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_image(void *mlx, t_image *texture)
{
	if (texture && texture->img)
		mlx_destroy_image(mlx, texture->img);
}

int	cleanup(t_game *game)
{
	destroy_image(game->window.mlx, game->north_texture);
	destroy_image(game->window.mlx, game->south_texture);
	destroy_image(game->window.mlx, game->west_texture);
	destroy_image(game->window.mlx, game->east_texture);
	destroy_image(game->window.mlx, game->render_image);
	destroy_image(game->window.mlx, game->minimap_bg);
	destroy_image(game->window.mlx, game->minimap_image);
	if (game->window.win)
	{
		mlx_destroy_window(game->window.mlx, game->window.win);
		game->window.win = NULL;
	}
	if (game->window.mlx)
	{
		mlx_destroy_display(game->window.mlx);
		free(game->window.mlx);
		game->window.mlx = NULL;
	}
	gc_clean();
	return (0);
}

int	update_position(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->keys.w)
		player_move(game, W_KEY);
	if (game->keys.a)
		player_move(game, A_KEY);
	if (game->keys.s)
		player_move(game, S_KEY);
	if (game->keys.d)
		player_move(game, D_KEY);
	if (game->keys.left)
		player_move(game, LEFT_ARROW_KEY);
	if (game->keys.right)
		player_move(game, RIGHT_ARROW_KEY);
	composite_frame(game);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->render_image->img, 0, 0);
	return (0);
}

static int	init_window(t_game *game)
{
	t_minimap	m_bg;
	t_mapinfo	map_info;

	game->window.win = mlx_new_window(game->window.mlx, game->window.width,
			game->window.height, "cub3d");
	if (!game->window.win)
		return (1);
	game->render_image = gc_malloc(sizeof(t_image));
	game->render_image->img = mlx_new_image(game->window.mlx,
			game->window.width, game->window.height);
	game->minimap_bg = gc_malloc(sizeof(t_image));
	game->minimap_bg->img = mlx_new_image(game->window.mlx, MINI_W, MINI_H);
	game->minimap_image = gc_malloc(sizeof(t_image));
	game->minimap_image->img = mlx_new_image(game->window.mlx, MINI_W, MINI_H);
	{
		get_map_info(game, &map_info);
		get_img_info(game->minimap_bg->img, &m_bg);
		draw_map_scaled(game, &m_bg, &map_info);
	}
	mlx_hook(game->window.win, DESTROY_NOTIFY, 0, &mlx_loop_end,
		game->window.mlx);
	mlx_hook(game->window.win, 2, 1L << 0, &key_press_handler, game);
	mlx_hook(game->window.win, 3, 1L << 1, &key_release_handler, game);
	mlx_loop_hook(game->window.mlx, &update_position, game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	game.window.win = NULL;
	game.window.width = 800;
	game.window.height = 600;
	check_args(argc, argv);
	game.window.mlx = mlx_init();
	if (!game.window.mlx)
	{
		ft_putendl_fd("Error: mlx_init failed.", 2);
		exit(1);
	}
	if (is_file_valid(&game, argv[1]) == 0 && is_map_valid(game.map) == 0)
	{
		if (init_window(&game) == 0)
			mlx_loop(game.window.mlx);
	}
	cleanup(&game);
	return (0);
}
