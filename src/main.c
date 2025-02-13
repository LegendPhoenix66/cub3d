/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:05:41 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/13 07:58:56 by ueharakeiji      ###   ########.fr       */
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
        (void) *game;
#endif
        free(game->window.mlx);
		game->window.mlx = NULL;
    }
    gc_clean();
    return (0);
}



void	print_game(t_game *game)
{
	int i;

	i = 0;
	printf("File Data:\n");
	printf("North Texture: %p\n", game->north_texture);
	printf("South Texture: %p\n", game->south_texture);
	printf("West Texture: %p\n", game->west_texture);
	printf("East Texture: %p\n", game->east_texture);
	printf("Floor Color: %d\n", game->floor_color);
	printf("Ceiling Color: %d\n", game->ceiling_color);
	printf("Map Lines:\n");
	for (i = 0; i < game->map_line_count; i++)
	{
		printf("%s\n", game->map[i]);
	}
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
	if (is_file_valid(&game, argv[1]) == 0)
	{
		print_game(&game);
		game.int_map = parsing_map(game.map, game.map_line_count);
		game.player_x = 3.5;
		game.player_y = 3.5;
		game.window.win = mlx_new_window(game.window.mlx, game.window.width,
				game.window.height, "cub3d");
		mlx_hook(game.window.win, DESTROY_NOTIFY, 0, &close_window,
			&game);
		mlx_key_hook(game.window.win, &esc_handler, game.window.mlx);
		draw_minimap(&game, game.int_map);
		mlx_loop(game.window.mlx);
	}
	cleanup(&game);
	return (0);
}
