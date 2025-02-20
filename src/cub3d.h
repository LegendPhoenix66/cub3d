/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:15:31 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/20 11:52:25 by ueharakeiji      ###   ########.fr       */
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

# define MINIMAP_WIDTH  200
# define MINIMAP_HEIGHT 200
# define MINIMAP_POS_X  10
# define MINIMAP_POS_Y  10

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
	int			floor_color;
	int			ceiling_color;
	t_image		*minimap_image;
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
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
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
	int	player_x;
	int	player_y;
	int	offset_x;
	int	offset_y;
	int	render_x;
	int	render_y;
	int	size;
}	t_player_draw;

// texture
typedef struct s_stripe
{
	t_image	*tex;
	int		tex_x;
	int		tex_y;
	int		tex_color;
	float	wall_x;
	int		y;
}				t_stripe;

typedef struct s_rayinit
{
	float	angle;
	float	camera;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}				t_rayinit;

typedef struct s_raydata
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	float	perp_wall_dist; // perpendicular wall distance
}				t_raydata;

typedef struct s_raycast
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		side;
	int		column_x;
}				t_raycast;

// check_args.c
void			check_args(int argc, char **argv);

// validate_file.c
int				is_file_valid(t_game *game, char *file);

// validate_map.c
int				is_map_valid(int **map);

// render_3d.c
void			render_3d(t_game *game);

// ray_init.c
void			init_ray_direction(t_game *game, int x,
					t_raydata *rd, t_raycast *rc);
void			init_ray_steps(t_game *game, t_raydata *rd, t_raycast *rc);
void			perform_dda(t_game *game, t_raydata *rd, t_raycast *rc);

// stripe_calc.c
void			calculate_stripe(t_game *game, t_raydata *rd, t_raycast *rc);
void			select_texture(t_game *game, t_raydata *rd,
					t_raycast *rc, t_stripe *s);
void			compute_tex_x(t_game *game, t_raydata *rd,
					t_raycast *rc, t_stripe *s);
void			adjust_draw_range(t_game *game, t_raycast *rc);

//stripe_draw.c
void			draw_stripe_wrapper(t_game *game, int *data,
					t_raycast *rc, t_raydata *rd);

// player_move.c
void			player_move(t_game *game, int keycode);

// drawing_minimap.c
void			draw_minimap(t_game *game);
// drawing_minimap_utils.c
void			get_map_info(t_game *game, t_mapinfo *info);
void			get_img_info(void *img, t_minimap *m);
void			set_tile_color(t_minimap *m, int tile);

// drawing_minimap_tiles.c
void			put_pixel_to_img(t_minimap *m, int x, int y, int color);
void			draw_map_scaled(t_game *game, t_minimap *m, t_mapinfo *info);

// hook_handler.c
int				esc_handler(int keycode, void *param);
int				movement_handler(int keycode, void *param);
int				close_window(void *param);

#endif // CUB3D_H
