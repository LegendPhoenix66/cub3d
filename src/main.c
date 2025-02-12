/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:05:41 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/12 20:41:36 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int cleanup(t_game *game)
{
    if (game->north_texture && game->north_texture->img)
        mlx_destroy_image(game->window.mlx, game->north_texture->img);
    if (game->south_texture && game->south_texture->img)
        mlx_destroy_image(game->window.mlx, game->south_texture->img);
    if (game->west_texture && game->west_texture->img)
        mlx_destroy_image(game->window.mlx, game->west_texture->img);
    if (game->east_texture && game->east_texture->img)
        mlx_destroy_image(game->window.mlx, game->east_texture->img);
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
        mlx_loop_end(game->window.mlx);
#endif
        free(game->window.mlx);
		game->window.mlx = NULL;
    }
    gc_clean();
    return (0);
}



void	print_game(t_game *game)
{
	printf("File Data:\n");
	printf("North Texture: %p\n", game->north_texture);
	printf("South Texture: %p\n", game->south_texture);
	printf("West Texture: %p\n", game->west_texture);
	printf("East Texture: %p\n", game->east_texture);
	printf("Floor Color: %d\n", game->floor_color);
	printf("Ceiling Color: %d\n", game->ceiling_color);
	printf("Map Lines:\n");
	for (int i = 0; i < 5; i++)
	{
		printf("%s\n", game->map[i]);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	game.window.mlx = mlx_init();
	game.window.win = NULL;
	game.window.width = 800;
	game.window.height = 600;
	check_args(argc, argv);
	if (is_file_valid(&game, argv[1]) == 0)
	{
		print_game(&game);
		game.window.win = mlx_new_window(game.window.mlx, game.window.width,
				game.window.height, "cub3d");
		mlx_hook(game.window.win, DESTROY_NOTIFY, 0, &close_window,
			&game);
		mlx_key_hook(game.window.win, &esc_handler, game.window.mlx);
		mlx_loop(game.window.mlx);
	}
	cleanup(&game);
	return (0);
}
