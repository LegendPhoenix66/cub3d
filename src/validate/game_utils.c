/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:10:37 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 18:10:37 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_max_columns(t_file_data *file_data)
{
	int	max_cols;
	int	current_row_length;
	int	y;

	max_cols = 0;
	y = 0;
	while (y < file_data->map_line_count)
	{
		current_row_length = ft_strlen(file_data->map_lines[y]);
		if (current_row_length > max_cols)
			max_cols = current_row_length;
		y++;
	}
	return (max_cols);
}

int	copy_map_to_game(t_game *game, t_file_data *file_data)
{
	int	max_cols;

	max_cols = get_max_columns(file_data);
	if (!allocate_map(game, file_data, max_cols))
		return (0);
	if (!copy_map_lines(game, file_data, max_cols))
		return (0);
	return (1);
}

t_image	*initialize_texture(void *mlx, char *file_path)
{
	t_image	*texture;

	texture = gc_malloc(sizeof(t_image));
	texture->img = mlx_xpm_file_to_image(mlx, file_path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (NULL);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_length, &texture->endian);
	return (texture);
}

int	rgb_to_hex(char *color_str)
{
	int		r;
	int		g;
	int		b;
	char	**rgb_values;

	r = 0;
	g = 0;
	b = 0;
	rgb_values = ft_split(color_str, ',');
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	free(rgb_values[0]);
	free(rgb_values[1]);
	free(rgb_values[2]);
	free(rgb_values);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_putstr_fd("Error: Invalid RGB color", 2);
		ft_putendl_fd(color_str, 2);
		return (-1);
	}
	return ((r << 16) | (g << 8) | b);
}

int	add_to_game(t_game *game, t_file_data *file_data)
{
	game->ceiling_color = rgb_to_hex(file_data->ceiling_color_str);
	game->floor_color = rgb_to_hex(file_data->floor_color_str);
	game->east_texture = initialize_texture(game->window.mlx,
			file_data->east_texture);
	game->north_texture = initialize_texture(game->window.mlx,
			file_data->north_texture);
	game->south_texture = initialize_texture(game->window.mlx,
			file_data->south_texture);
	game->west_texture = initialize_texture(game->window.mlx,
			file_data->west_texture);
	return (copy_map_to_game(game, file_data));
}
