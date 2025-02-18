/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:15:31 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/18 15:01:06 by lhopp            ###   ########.fr       */
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

#define MINIMAP_WIDTH  200
#define MINIMAP_HEIGHT 200
#define MINIMAP_POS_X  10
#define MINIMAP_POS_Y  10

# include "../libft/libft.h"
# include "garbage_collection/gc.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <math.h>

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
	void		*addr;       
	int			width;
	int			height;
	int			bpp;        
	int			line_length;
	int			endian;    
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
    t_image     *floor;
    t_image     *ceiling;
}				t_game;

typedef struct s_minimap
{
	int		cell_size;
	double	dir_x;
	double	dir_y;
	int		color;
	float	player_center_x;
	float	player_center_y;
	char	*img_data;
	int		img_size_line;
}	t_minimap;

// tile related
typedef struct s_area
{
	int	sx;
	int	sy;
	int	ex;
	int	ey;
}	t_area;

typedef struct s_mapinfo
{
	int		width;
	int		height;
	float	scale;
}	t_mapinfo;

// structure for tile calculation
typedef struct s_draw_map
{
	int	row;
	int	col;
	int	tile;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}	t_draw_map;

// draw player related
typedef struct s_player_draw
{
	int px;
	int py;
	int dx;
	int dy;
	int rx;
	int ry;
	int size;
}	t_player_draw;



// check_args.c
void			check_args(int argc, char **argv);

// validate_file.c
int				is_file_valid(t_game *game, char *file);

// validate_map.c
int				validate_map_closed(t_game *game);

//render_3d.c
void			render_3d(t_game *game);

// player_move.c
void			player_move(t_game *game, int keycode);

// drawing_minimap.c
void			draw_minimap(t_game *game);
// drawing_minimap_utils.c
void	get_map_info(t_game *game, t_mapinfo *info);
void	get_img_info(void *img, t_minimap *m);
void	set_tile_color(t_minimap *m, int tile);

// drawing_minimap_tiles.c
void	put_pixel_to_img(t_minimap *m, int x, int y, int color);
void	draw_map_scaled(t_game *game, t_minimap *m, t_mapinfo *info);

// hook_handler.c
int				esc_handler(int keycode, void *param);
int movement_handler(int keycode, void *param);
int				close_window(void *param);

#endif // CUB3D_H
