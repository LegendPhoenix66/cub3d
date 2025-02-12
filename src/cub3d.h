/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:15:31 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/12 19:28:24 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __APPLE__
#  define ESC_KEY 53 // macOS Escape key
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define LEFT_ARROW_KEY 123
#  define RIGHT_ARROW_KEY 124
#  define IS_LINUX 2
# elif defined(__linux__)
#  include <X11/keysym.h>
#  define ESC_KEY XK_Escape
#  define W_KEY XK_w
#  define A_KEY XK_a
#  define S_KEY XK_s
#  define D_KEY XK_d
#  define LEFT_ARROW_KEY XK_Left
#  define RIGHT_ARROW_KEY XK_Right
#  define IS_LINUX 1
# endif

# define DESTROY_NOTIFY 17

# include "../libft/libft.h"
# include "garbage_collection/gc.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>

typedef struct s_file_data
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*floor_color_str;
	char		*ceiling_color_str;
	char		**map_lines;
	int			map_line_count;
}				t_file_data;

typedef struct s_image
{
	void		*img;
	int			width;
	int			height;
}				t_image;

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
	char		**map;
	t_image		*east_texture;
	t_image		*north_texture;
	t_image		*south_texture;
	t_image		*west_texture;
	int			floor_color;
	int			ceiling_color;
}				t_game;

// check_args.c
void			check_args(int argc, char **argv);

// validate_file.c
int				is_file_valid(t_game *game, char *file);

// validate_map.c

// hook_handler.c
int				esc_handler(int keycode, void *mlx);

#endif // CUB3D_H
