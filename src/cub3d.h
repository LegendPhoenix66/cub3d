/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:15:31 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 18:48:35 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/keysym.h>
# define ESC_KEY XK_Escape
# define W_KEY XK_w
# define A_KEY XK_a
# define S_KEY XK_s
# define D_KEY XK_d
# define LEFT_ARROW_KEY XK_Left
# define RIGHT_ARROW_KEY XK_Right

# define DESTROY_NOTIFY 17

# define MINI_W 200
# define MINI_H 200
# define MINIMAP_POS_X 10
# define MINIMAP_POS_Y 10

# include "../libft/libft.h"
# include "garbage_collection/gc.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>

typedef struct s_file_data
{
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*floor_color_str;
	char			*ceiling_color_str;
	char			**map_lines;
	int				map_line_count;
}					t_file_data;

typedef struct s_image
{
	void			*img;
	void			*addr;
	int				width;
	int				height;
	int				bpp;
	int				line_length;
	int				endian;
}					t_image;

typedef struct s_player
{
	float			x_pos;
	float			y_pos;
	int				orientation;
}					t_player;

typedef struct s_movement_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
}					t_movement_keys;

typedef struct s_window
{
	void			*mlx;
	void			*win;
	int				height;
	int				width;
}					t_window;

typedef struct s_mapinfo
{
	int				width;
	int				height;
	float			scale;
}					t_mapinfo;

typedef struct s_game
{
	t_window		window;
	t_player		player;
	t_movement_keys	keys;
	int				**map;
	t_image			*east_texture;
	t_image			*north_texture;
	t_image			*south_texture;
	t_image			*west_texture;
	int				floor_color;
	int				ceiling_color;
	t_image			*minimap_bg;
	t_image			*minimap_image;
	t_image			*render_image;
	t_mapinfo		mapinfo;
}					t_game;

typedef struct s_minimap
{
	int				cell_size;
	double			dir_x;
	double			dir_y;
	int				color;
	float			player_center_x;
	float			player_center_y;
	char			*img_data;
	int				img_size_line;
}					t_minimap;

// tile related
typedef struct s_area
{
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
}					t_area;

// structure for tile calculation
typedef struct s_draw_map
{
	int				row;
	int				col;
	int				tile;
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
}					t_draw_map;

// draw player related
typedef struct s_player_draw
{
	int				player_x;
	int				player_y;
	int				offset_x;
	int				offset_y;
	int				render_x;
	int				render_y;
	int				size;
}					t_player_draw;

// texture
typedef struct s_stripe
{
	t_image			*tex;
	int				tex_x;
	int				tex_y;
	int				tex_color;
	float			wall_x;
	int				y;
}					t_stripe;

typedef struct s_rayinit
{
	float			angle;
	float			camera;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
}					t_rayinit;

typedef struct s_raydata
{
	float			ray_dir_x;
	float			ray_dir_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			side_dist_x;
	float			side_dist_y;
	float			perp_wall_dist;
}					t_raydata;

typedef struct s_raycast
{
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				side;
	int				column_x;
}					t_raycast;

// frame composition
typedef struct s_blit
{
	char			*render_data;
	int				render_line;
	int				bytes_per_row;
	int				y;
	int				src_offset;
	int				dest_offset;
}					t_blit;

// check_args.c
void				check_args(int argc, char **argv);

// validate_file.c
int					is_file_valid(t_game *game, char *file);

// render_3d.c
void				render_3d(t_game *game);
void				raycast_column(t_game *game, int x, int *data);
void				draw_floor_and_ceiling(t_game *game, int *data);

// ray_init.c
void				init_ray_direction(t_game *game, int x, t_raydata *rd,
						t_raycast *rc);
void				init_ray_steps(t_game *game, t_raydata *rd, t_raycast *rc);
void				perform_dda(t_game *game, t_raydata *rd, t_raycast *rc);

// stripe_calc.c
void				calculate_stripe(t_game *game, t_raydata *rd,
						t_raycast *rc);
void				select_texture(t_game *game, t_raydata *rd, t_raycast *rc,
						t_stripe *s);
void				compute_tex_x(t_game *game, t_raydata *rd, t_raycast *rc,
						t_stripe *s);
void				adjust_draw_range(t_game *game, t_raycast *rc);

// stripe_draw.c
void				draw_stripe_wrapper(t_game *game, int *data, t_raycast *rc,
						t_raydata *rd);

// player_move.c
void				player_move(t_game *game, int keycode);

// drawing_minimap.c
void				draw_minimap(t_game *game);
void				draw_player_scaled(t_game *game, t_minimap *m, float scale);

// drawing_minimap_utils.c
void				get_map_info(t_game *game, t_mapinfo *info);
void				get_img_info(void *img, t_minimap *m);
void				set_tile_color(t_minimap *m, int tile);

// drawing_minimap_tiles.c
void				put_pixel_to_img(t_minimap *m, int x, int y, int color);
void				draw_map_scaled(t_game *game, t_minimap *m,
						t_mapinfo *info);

// hook_handler.c
int					key_press_handler(int keycode, void *param);
int					key_release_handler(int keycode, void *param);

// main.c
int					cleanup(t_game *game);

// composite_frame.c
void				composite_frame(t_game *game);

// map_processing.c
int					process_map_line(t_file_data *file_data, char *line);
int					copy_map_lines(t_game *game, t_file_data *file_data,
						int max_columns);
int					allocate_map(t_game *game, t_file_data *file_data,
						int max_cols);

// color_processing.c
int					process_color_line(t_file_data *file_data,
						const char *line);

// texture_processing.c
int					process_texture_line(t_file_data *file_data, char *line);

// file_utils.c
int					is_space(char c);
int					is_empty_line(const char *line);
int					handle_error(char *msg);

// file_reader.c
int					open_file(const char *file, char **content);
char				*get_next_line(char **content_ptr);

// game_utils.c
int					add_to_game(t_game *game, t_file_data *file_data);

// map_validation.c
int					validate_player_count(char **map_lines, int map_line_count);
int					is_valid_map_line(const char *line);

// validate_map.c
int					is_map_valid(int **map);

// file_init.c
t_file_data			*init_file_data(void);

#endif // CUB3D_H
