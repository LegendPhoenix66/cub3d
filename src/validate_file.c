/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:43:58 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/13 16:46:51 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_file_data	*init_file_data(void)
{
	t_file_data	*file_data;

	file_data = gc_malloc(sizeof(t_file_data));
	file_data->north_texture = NULL;
	file_data->south_texture = NULL;
	file_data->west_texture = NULL;
	file_data->east_texture = NULL;
	file_data->floor_color_str = NULL;
	file_data->ceiling_color_str = NULL;
	file_data->map_lines = NULL;
	file_data->map_line_count = 0;
	return (file_data);
}

int	open_file(char *file, char **content)
{
	int		fd;
	char	*buffer;
	size_t	chunk_size;
	ssize_t	bytes_read;
	size_t	total_size;

	chunk_size = 1024;
	total_size = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error: Could not open file", 2);
		return (1);
	}
	*content = gc_malloc(1);
	if (!*content)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		close(fd);
		return (1);
	}
	(*content)[0] = '\0';
	buffer = gc_malloc(chunk_size + 1);
	if (!buffer)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		close(fd);
		return (1);
	}
	while ((bytes_read = read(fd, buffer, chunk_size)) > 0)
	{
		buffer[bytes_read] = '\0';
		*content = gc_realloc(*content, total_size + bytes_read + 1);
		if (!*content)
		{
			ft_putendl_fd("Error: Memory allocation failed", 2);
			close(fd);
			return (1);
		}
		ft_memcpy(*content + total_size, buffer, bytes_read);
		total_size += bytes_read;
		(*content)[total_size] = '\0';
	}
	if (bytes_read == -1)
	{
		ft_putendl_fd("Error: Failed to read the file", 2);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_empty_line(const char *line)
{
	for (int i = 0; line[i] != '\0'; i++)
	{
		if (!is_space(line[i]))
		{
			return (0); // Not empty
		}
	}
	return (1); // Empty
}

int	process_texture_line(t_file_data *file_data, char *line)
{
	char	*texture_path;

	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		texture_path = gc_strdup(line + 3);
	}
	else
	{
		return (0);
	}
	if (access(texture_path, F_OK) != 0)
	{
		ft_putstr_fd("Error: Texture file not found: ", 2);
		ft_putendl_fd(texture_path, 2);
		gc_free(texture_path);
		return (0);
	}
	if (ft_strncmp(line, "NO ", 3) == 0)
		file_data->north_texture = texture_path;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		file_data->south_texture = texture_path;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		file_data->west_texture = texture_path;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		file_data->east_texture = texture_path;
	return (1);
}

int	process_color_line(t_file_data *file_data, const char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		file_data->floor_color_str = gc_strdup(line + 2);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		file_data->ceiling_color_str = gc_strdup(line + 2);
	}
	else
	{
		return (0);
	}
	return (1);
}

int	is_valid_character(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

int	is_valid_map_line(const char *line)
{
	for (int i = 0; line[i] != '\0'; i++)
	{
		if (!is_valid_character(line[i]))
		{
			ft_putstr_fd("Error: Invalid character in map: ", 2);
			ft_putchar_fd(line[i], 2);
			ft_putchar_fd('\n', 2);
			return (0); // Invalid character found
		}
	}
	return (1); // Line is valid
}

int	process_map_line(t_file_data *file_data, char *line)
{
	char	**new_map_lines;

	if (!is_valid_map_line(line))
	{
		return (-1);
	}
	new_map_lines = gc_realloc(file_data->map_lines, sizeof(char *)
			* (file_data->map_line_count + 1));
	if (!new_map_lines)
	{
		return (-1);
	}
	file_data->map_lines = new_map_lines;
	file_data->map_lines[file_data->map_line_count] = line;
	file_data->map_line_count++;
	return (0);
}

void	print_missing_config(t_file_data *file_data)
{
	if (!file_data->north_texture)
		ft_putendl_fd("Error: Missing north texture (NO).", 2);
	if (!file_data->south_texture)
		ft_putendl_fd("Error: Missing south texture (SO).", 2);
	if (!file_data->west_texture)
		ft_putendl_fd("Error: Missing west texture (WE).", 2);
	if (!file_data->east_texture)
		ft_putendl_fd("Error: Missing east texture (EA).", 2);
	if (!file_data->floor_color_str)
		ft_putendl_fd("Error: Missing floor color (F).", 2);
	if (!file_data->ceiling_color_str)
		ft_putendl_fd("Error: Missing ceiling color (C).", 2);
}

int	is_config_complete(t_file_data *file_data)
{
	return (file_data->north_texture && file_data->south_texture
		&& file_data->west_texture && file_data->east_texture
		&& file_data->floor_color_str && file_data->ceiling_color_str);
}

int	process_config_line(t_file_data *file_data, char *line)
{
	char	*value_start;

	value_start = line;
	while (is_space(*value_start))
		value_start++;
	if (process_texture_line(file_data, value_start))
	{
		return (0);
	}
	else if (process_color_line(file_data, value_start))
	{
		return (0);
	}
	else
	{
		if (!is_config_complete(file_data))
		{
			print_missing_config(file_data);
			return (1);
		}
		return (process_map_line(file_data, line));
	}
}

char	*get_next_line(char **content_ptr)
{
	char	*line_start;
	char	*line_end;
	char	*line;

	if (!*content_ptr || **content_ptr == '\0')
		return (NULL);
	line_start = *content_ptr;
	line_end = ft_strchr(line_start, '\n');
	line = NULL;
	if (line_end)
	{
		line = gc_malloc(line_end - line_start + 1);
		if (!line)
			return (NULL);
		ft_memcpy(line, line_start, line_end - line_start);
		line[line_end - line_start] = '\0';
		*content_ptr = line_end + 1;
	}
	else
	{
		line = gc_strdup(line_start);
		if (!line)
			return (NULL);
		*content_ptr = NULL;
	}
	return (line);
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

int	copy_map_to_game(t_game *game, t_file_data *file_data)
{
	int	y;
	int	x;

	game->map = gc_malloc(sizeof(int *) * file_data->map_line_count);
	if (!game->map)
		return (0);
	for (y = 0; y < file_data->map_line_count; y++)
	{
		game->map[y] = gc_malloc(sizeof(int)
				* ft_strlen(file_data->map_lines[y]));
		if (!game->map[y])
			return (0);
	}
	for (y = 0; y < file_data->map_line_count; y++)
	{
		for (x = 0; file_data->map_lines[y][x] != '\0'; x++)
		{
			if (file_data->map_lines[y][x] == '0')
				game->map[y][x] = 0;
			else if (file_data->map_lines[y][x] == '1')
				game->map[y][x] = 1;
			else if (file_data->map_lines[y][x] == ' ')
				game->map[y][x] = -1;
			else if (file_data->map_lines[y][x] == 'N'
				|| file_data->map_lines[y][x] == 'S'
				|| file_data->map_lines[y][x] == 'E'
				|| file_data->map_lines[y][x] == 'W')
			{
				game->player.x_pos = x;
				game->player.y_pos = y;
				if (file_data->map_lines[y][x] == 'N')
					game->player.orientation = 0;
				else if (file_data->map_lines[y][x] == 'S')
					game->player.orientation = 180;
				else if (file_data->map_lines[y][x] == 'E')
					game->player.orientation = 90;
				else if (file_data->map_lines[y][x] == 'W')
					game->player.orientation = 270;
				game->map[y][x] = 0;
			}
			else
			{
				ft_putstr_fd("Error: Invalid character in map: ", 2);
				ft_putchar_fd(file_data->map_lines[y][x], 2);
				ft_putchar_fd('\n', 2);
				return (0);
			}
		}
	}
	return (1);
}

int	add_to_game(t_game *game, t_file_data *file_data)
{
	game->ceiling_color = rgb_to_hex(file_data->ceiling_color_str);
	game->floor_color = rgb_to_hex(file_data->floor_color_str);
	game->east_texture = gc_malloc(sizeof(t_image));
	game->east_texture->img = mlx_xpm_file_to_image(game->window.mlx,
			file_data->east_texture, &game->east_texture->width,
			&game->east_texture->height);
	game->north_texture = gc_malloc(sizeof(t_image));
	game->north_texture->img = mlx_xpm_file_to_image(game->window.mlx,
			file_data->north_texture, &game->north_texture->width,
			&game->north_texture->height);
	game->south_texture = gc_malloc(sizeof(t_image));
	game->south_texture->img = mlx_xpm_file_to_image(game->window.mlx,
			file_data->south_texture, &game->south_texture->width,
			&game->south_texture->height);
	game->west_texture = gc_malloc(sizeof(t_image));
	game->west_texture->img = mlx_xpm_file_to_image(game->window.mlx,
			file_data->west_texture, &game->west_texture->width,
			&game->west_texture->height);
	return (copy_map_to_game(game, file_data));
}

int	validate_content(t_game *game, char *content)
{
	t_file_data	*file_data;
	char		*current_content_ptr;
	char		*line;

	(void)game;
	if (!content)
		return (1);
	file_data = init_file_data();
	if (!file_data)
		return (1);
	current_content_ptr = content;
	while ((line = get_next_line(&current_content_ptr)) != NULL)
	{
		if (is_empty_line(line))
		{
			continue ;
		}
		if (process_config_line(file_data, line) != 0)
		{
			return (1);
		}
	}
	add_to_game(game, file_data);
	return (0);
}

int	is_file_valid(t_game *game, char *file)
{
	char	*content;

	if (open_file(file, &content) != 0)
	{
		ft_putstr_fd("Error: Could not open file", 2);
		ft_putendl_fd(file, 2);
		return (1);
	}
	if (validate_content(game, content) != 0)
	{
		ft_putstr_fd("Error: Invalid file", 2);
		ft_putendl_fd(file, 2);
		return (1);
	}
	return (0);
}
