/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:15:31 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/13 20:24:58 by lhopp            ###   ########.fr       */
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
#  define IS_LINUX 0
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

typedef struct s_player
{
	float		x_pos;
	float		y_pos;
	int			orientation;
}				t_player;

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
	t_player	player;
	int			**map;
	t_image		*east_texture;
	t_image		*north_texture;
	t_image		*south_texture;
	t_image		*west_texture;
	int			floor_color;
	int			ceiling_color;
}				t_game;

typedef struct s_minimap
{
	int		cell_size;
	int		offset_x;
	int		offset_y;
	double	dir_x;
	double	dir_y;
	int		color;
	int		player_center_x;
	int		player_center_y;
}	t_minimap;


// check_args.c
void			check_args(int argc, char **argv);

// validate_file.c
int				is_file_valid(t_game *game, char *file);

// validate_map.c

// parsing_map.c
int				**parsing_map(char **map, int map_line_count);

// drawing_minimap.c
//void	fill_one_cell(t_game *game, t_minimap *m, int row, int col);
//void	draw_map_cells(t_game *game, int **int_map, t_minimap *m);
//void	draw_player(t_game *game, t_minimap *m);
void	draw_minimap(t_game *game);

// hook_handler.c
int				esc_handler(int keycode, void *mlx);
int				close_window(void *param);
#endif // CUB3D_H
