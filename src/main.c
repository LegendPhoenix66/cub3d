/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:05:41 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/20 17:39:28 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cleanup(t_game *game)
{
	if (game->north_texture && game->north_texture->img)
		mlx_destroy_image(game->window.mlx, game->north_texture->img);
	if (game->south_texture && game->south_texture->img)
		mlx_destroy_image(game->window.mlx, game->south_texture->img);
	if (game->west_texture && game->west_texture->img)
		mlx_destroy_image(game->window.mlx, game->west_texture->img);
	if (game->east_texture && game->east_texture->img)
		mlx_destroy_image(game->window.mlx, game->east_texture->img);
	if (game->minimap_image && game->minimap_image->img)
		mlx_destroy_image(game->window.mlx, game->minimap_image->img);
	if (game->window.win)
	{
		mlx_destroy_window(game->window.mlx, game->window.win);
		game->window.win = NULL;
	}
	if (game->window.mlx)
	{
#ifdef __linux__
		mlx_destroy_display(game->window.mlx);
#else
		(void)*game;
#endif
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
	render_3d(game);
	draw_minimap(game);
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
		game.window.win = mlx_new_window(game.window.mlx, game.window.width,
				game.window.height, "cub3d");
		mlx_hook(game.window.win, DESTROY_NOTIFY, 0, &close_window, &game);
		mlx_hook(game.window.win, 2, 1L << 0, &key_press_handler, &game);
		mlx_hook(game.window.win, 3, 1L << 1, &key_release_handler, &game);
		mlx_loop_hook(game.window.mlx, &update_position, &game);
		render_3d(&game);
		draw_minimap(&game);
		mlx_loop(game.window.mlx);
	}
	cleanup(&game);
	return (0);
}
