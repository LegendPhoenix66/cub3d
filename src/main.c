/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:05:41 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/09 11:51:04 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cleanup(t_window *window)
{
	if (window->win)
		mlx_destroy_window(window->mlx, window->win);
	if (window->mlx)
	{
		mlx_destroy_display(window->mlx);
		free(window->mlx);
	}
	gc_clean();
	return (0);
}

int	main(int argc, char **argv)
{
	t_window	window;

	window.mlx = mlx_init();
	window.win = NULL;
	window.width = 800;
	window.height = 600;
	// check arguments, map, etc.
	check_args(argc, argv);
    // validate_map
	window.win = mlx_new_window(window.mlx, window.width, window.height,
			"cub3d");
	mlx_hook(window.win, DESTROY_NOTIFY, 0, &mlx_loop_end, window.mlx);
	mlx_key_hook(window.win, &esc_handler, window.mlx);
	mlx_loop(window.mlx);
	cleanup(&window);
	return (0);
}
