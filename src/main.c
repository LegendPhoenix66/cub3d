/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:05:41 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/10 18:54:26 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cleanup(t_game *game)
{
	if (game->window.win)
		mlx_destroy_window(game->window.mlx, game->window.win);
	if (game->window.mlx)
	{
		mlx_destroy_display(game->window.mlx);
		free(game->window.mlx);
	}
	gc_clean();
	return (0);
}

void print_game(t_game *game)
{
    printf("File Data:\n");
    printf("North Texture: %p\n", game->north_texture);
    printf("South Texture: %p\n", game->south_texture);
    printf("West Texture: %p\n", game->west_texture);
    printf("East Texture: %p\n", game->east_texture);
    printf("Floor Color: %d\n", game->floor_color);
    printf("Ceiling Color: %d\n", game->ceiling_color);
    printf("Map Lines:\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", game->map[i]);
    }
}

int	main(int argc, char **argv)
{
    t_game  game;

	game.window.mlx = mlx_init();
    game.window.win = NULL;
    game.window.width = 800;
    game.window.height = 600;
	check_args(argc, argv);
	if (is_file_valid(&game, argv[1]) == 0)
	{
        print_game(&game);
		game.window.win = mlx_new_window(game.window.mlx, game.window.width, game.window.height,
				"cub3d");
		mlx_hook(game.window.win, DESTROY_NOTIFY, 0, &mlx_loop_end, game.window.mlx);
		mlx_key_hook(game.window.win, &esc_handler, game.window.mlx);
		mlx_loop(game.window.mlx);
	}
	cleanup(&game);
	return (0);
}
