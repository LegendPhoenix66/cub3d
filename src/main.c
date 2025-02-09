/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:05:41 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/09 09:54:43 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
#include <stdio.h>
#include "garbage_collection/gc.h"

int main(void) {
    char *string_ptr;
    string_ptr = (char *)gc_malloc(sizeof(char) * 20);
    sprintf(string_ptr, "Hello GC Simple!");
    printf("Allocated string: %s\n", string_ptr);
    gc_free(string_ptr);

    string_ptr = (char *)gc_malloc(sizeof(char) * 20);
    sprintf(string_ptr, "no free");
    printf("Allocated string: %s\n", string_ptr);
    gc_free(string_ptr);
    printf("Program compiles and runs successfully!\n");
    gc_clean();
    return 0;
}
*/

#include "cub3d.h"
#include <stdlib.h>

/*to check ".cub"*/
int is_valid_extension(const char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (filename[len - 4] == '.' && filename[len - 3] == 'c'
		&& filename[len - 2] == 'u' && filename[len - 1] == 'b')
		return (1);
	return (0);
}

/*template for key enter event. now only esc key*/
int key_hook(int keycode, t_game *game)
{
    printf("Key Pressed: %d\n", keycode); //debag.display keycode pushed

    if (keycode == 65307) 
    {
        printf("ESC key detected. Exiting...\n");
        mlx_destroy_window(game->mlx, game->win);
        gc_clean();
        exit(0);
    }
    return (0);
}


/*exit when x button on window pushed*/
int exit_hook(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	gc_clean();
	exit(0);
	return (0);
}


int main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	if (!is_valid_extension(argv[1]))
	{
		printf("Error\nInvalid file extension. Expected .cub\n");
		return (1);
	}
	game = gc_malloc(sizeof(t_game));
	if (!game)
	{
		printf("Error\nMemory allocation failed.\n");
		return (1);
	}
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error\nMLX initialization failed.\n");
		return (1);
	}
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
	{
		printf("Error\nWindow creation failed.\n");
		return (1);
	}
	mlx_key_hook(game->win, key_hook, game);  // key push
	mlx_hook(game->win, 17, 0, exit_hook, game);   // x button push
	mlx_loop(game->mlx);
	gc_clean();
	return (0);
}
