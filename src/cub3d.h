/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:15:31 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/10 13:53:54 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __APPLE__
#  define ESC_KEY 53 // macOS Escape key
# elif defined(__linux__)
#  include <X11/keysym.h>
#  define ESC_KEY XK_Escape
# endif

# define DESTROY_NOTIFY 17

# include "../libft/libft.h"
# include "garbage_collection/gc.h"
# include <mlx.h>
# include <stdio.h>

typedef struct s_window
{
	void		*mlx;
	void		*win;
	int			height;
	int			width;
}				t_window;

typedef struct s_game
{
    t_window	window;
}				t_game;

// check_args.c
void		check_args(int argc, char **argv);

// hook_handler.c
int				esc_handler(int keycode, void *mlx);

#endif // CUB3D_H
