/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuehara <kuehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:52:28 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/17 21:44:45 by kuehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

/*
** この関数はウィンドウの上半分に天井テクスチャ、下半分に床テクスチャを
** タイル状に貼り付けます。
*/
static void	fill_ceiling_and_floor(t_game *game, int *data)
{
	int			win_w = game->window.width;
	int			win_h = game->window.height;
	t_image		*ceil_tex = game->ceiling;
	t_image		*floor_tex = game->floor;
	int			x, y;
	int			texX, texY;
	int			color;

	// 天井 (上半分)
	for (y = 0; y < win_h / 2; y++)
	{
		for (x = 0; x < win_w; x++)
		{
			texX = (x * ceil_tex->width) / win_w;
			texY = (y * ceil_tex->height) / (win_h / 2);
			if (texX < 0) texX = 0;
			if (texX >= ceil_tex->width)
				texX = ceil_tex->width - 1;
			if (texY < 0) texY = 0;
			if (texY >= ceil_tex->height)
				texY = ceil_tex->height - 1;
			color = ((int *)ceil_tex->addr)[texY * ceil_tex->width + texX];
			data[y * win_w + x] = color;
		}
	}

	// 床 (下半分)
	for (y = win_h / 2; y < win_h; y++)
	{
		for (x = 0; x < win_w; x++)
		{
			texX = (x * floor_tex->width) / win_w;
			texY = ((y - (win_h / 2)) * floor_tex->height) / (win_h / 2);
			if (texX < 0) texX = 0;
			if (texX >= floor_tex->width)
				texX = floor_tex->width - 1;
			if (texY < 0) texY = 0;
			if (texY >= floor_tex->height)
				texY = floor_tex->height - 1;
			color = ((int *)floor_tex->addr)[texY * floor_tex->width + texX];
			data[y * win_w + x] = color;
		}
	}
}

/* 以下、壁のレイキャスト処理は変更なし */

static void	init_ray_vars(t_game *game, int x, float *f, int *i)
{
	float	angle;
	float	cam;
	float	dx;
	float	dy;
	float	planeX;
	float	planeY;

	angle = game->player.orientation * (M_PI / 180.0f);
	cam = (2.0f * x / (float)game->window.width) - 1.0f;
	dx = sin(angle);
	dy = -cos(angle);
	planeX = 0.66 * cos(angle);
	planeY = 0.66 * sin(angle);
	f[1] = dx + planeX * cam;
	f[2] = dy + planeY * cam;
	i[0] = (int)game->player.x_pos;
	i[1] = (int)game->player.y_pos;
	f[3] = (f[1] == 0) ? 1e30f : fabs(1.0f / f[1]);
	f[4] = (f[2] == 0) ? 1e30f : fabs(1.0f / f[2]);
	i[2] = (f[1] < 0) ? -1 : 1;
	f[5] = (f[1] < 0) ? (game->player.x_pos - i[0]) * f[3]
		: (((float)i[0] + 1.0f) - game->player.x_pos) * f[3];
	i[3] = (f[2] < 0) ? -1 : 1;
	f[6] = (f[2] < 0) ? (game->player.y_pos - i[1]) * f[4]
		: (((float)i[1] + 1.0f) - game->player.y_pos) * f[4];
	i[7] = -1;
}

static void	perform_dda(t_game *game, float *f, int *i)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (f[5] < f[6])
		{
			f[5] += f[3];
			i[0] += i[2];
			i[7] = 0;
		}
		else
		{
			f[6] += f[4];
			i[1] += i[3];
			i[7] = 1;
		}
		if (i[0] < 0 || i[1] < 0)
			hit = 1;
		else if (game->map[i[1]] == NULL)
			hit = 1;
		else if (game->map[i[1]][i[0]] == INT_MIN)
			hit = 1;
		else if (game->map[i[1]][i[0]] == 1)
			hit = 1;
	}
}

static void	calculate_stripe(t_game *game, float *f, int *i)
{
	float	perp;

	if (i[7] == 0)
		perp = ((float)i[0] - game->player.x_pos + (1 - i[2]) / 2.0f) / f[1];
	else
		perp = ((float)i[1] - game->player.y_pos + (1 - i[3]) / 2.0f) / f[2];
	f[7] = perp;
	i[4] = (int)(game->window.height / perp);
	i[5] = -i[4] / 2 + game->window.height / 2;
	i[6] = i[5] + i[4];
}

static void	draw_stripe(t_game *game, int x, int *data, int *i, float *f)
{
	int			y;
	int			tex_x;
	int			tex_y;
	int			tex_color;
	t_image		*tex;
	float		wallX;

	if (i[7] == 0)
		tex = (f[1] > 0) ? game->west_texture : game->east_texture;
	else
		tex = (f[2] > 0) ? game->north_texture : game->south_texture;
	if (!tex || !tex->addr)
	{
		ft_putendl_fd("Error: Texture not loaded", 2);
		return;
	}
	if (i[7] == 0)
		wallX = game->player.y_pos + f[7] * f[2];
	else
		wallX = game->player.x_pos + f[7] * f[1];
	wallX -= floor(wallX);
	tex_x = (int)(wallX * tex->width);
	if (i[7] == 0 && f[1] > 0)
		tex_x = tex->width - tex_x - 1;
	if (i[7] == 1 && f[2] < 0)
		tex_x = tex->width - tex_x - 1;
	if (i[5] < 0)
		i[5] = 0;
	if (i[6] >= game->window.height)
		i[6] = game->window.height - 1;
	y = i[5];
	while (y < i[6])
	{
		int d = y * 256 - game->window.height * 128 + i[4] * 128;
		tex_y = ((d * tex->height) / i[4]) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_color = ((int *)tex->addr)[tex_y * tex->width + tex_x];
		data[y * game->window.width + x] = tex_color;
		y++;
	}
}

static void	raycast_column(t_game *game, int x, int *data)
{
	float	f[9];
	int		i[8];

	init_ray_vars(game, x, f, i);
	perform_dda(game, f, i);
	calculate_stripe(game, f, i);
	draw_stripe(game, x, data, i, f);
}

void	render_3d(t_game *game)
{
	void	*img;
	int		*data;
	int		x;
	int		arr[3];

	// ウィンドウ全体サイズのイメージを作成
	img = mlx_new_image(game->window.mlx, game->window.width, game->window.height);
	data = (int *)mlx_get_data_addr(img, &arr[0], &arr[1], &arr[2]);

	// まず天井と床をテクスチャで塗りつぶす
	fill_ceiling_and_floor(game, data);

	// その上から壁をレイキャストで描画
	x = 0;
	while (x < game->window.width)
	{
		raycast_column(game, x, data);
		x++;
	}
	mlx_put_image_to_window(game->window.mlx, game->window.win, img, 0, 0);
	mlx_destroy_image(game->window.mlx, img);
}
