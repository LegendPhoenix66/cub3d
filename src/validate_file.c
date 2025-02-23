/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:43:58 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 16:58:26 by lhopp            ###   ########.fr       */
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

int	append_buffer(char **content, const char *buffer, size_t bytes_read,
		size_t *total_size)
{
	char	*new_content;

	new_content = gc_realloc(*content, *total_size + bytes_read + 1);
	if (!new_content)
		return (1);
	*content = new_content;
	ft_memcpy(*content + *total_size, buffer, bytes_read);
	*total_size += bytes_read;
	(*content)[*total_size] = '\0';
	return (0);
}

static int	handle_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (1);
}

static ssize_t	read_and_process(int fd, char *buffer, char **content,
		size_t *total_size)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, 1024);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (append_buffer(content, buffer, bytes_read, total_size) == 1)
			return (handle_error("Error: Memory allocation failed"));
		bytes_read = read(fd, buffer, 1024);
	}
	return (bytes_read);
}

int	read_file_content(int fd, char **content)
{
	char	*buffer;
	size_t	total_size;
	ssize_t	read_status;

	total_size = 0;
	buffer = gc_malloc(1025);
	if (!buffer)
		return (handle_error("Error: Memory allocation failed"));
	read_status = read_and_process(fd, buffer, content, &total_size);
	if (read_status == -1)
		return (handle_error("Error: Failed to read the file"));
	return (0);
}

int	open_file(const char *file, char **content)
{
	int	fd;

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
	if (read_file_content(fd, content) == 1)
	{
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
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_space(line[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	process_texture_line(t_file_data *file_data, char *line)
{
	char	*texture_path;

	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		texture_path = gc_strdup(line + 3);
	else
		return (0);
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
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_valid_character(line[i]))
		{
			ft_putstr_fd("Error: Invalid character in map: ", 2);
			ft_putchar_fd(line[i], 2);
			ft_putchar_fd('\n', 2);
			return (0);
		}
		i++;
	}
	return (1);
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

int	count_players(char **map_lines, int map_line_count)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	while (i < map_line_count)
	{
		j = 0;
		while (map_lines[i][j] != '\0')
		{
			if (map_lines[i][j] == 'N' || map_lines[i][j] == 'S'
				|| map_lines[i][j] == 'E' || map_lines[i][j] == 'W')
			{
				player_count++;
			}
			j++;
		}
		i++;
	}
	return (player_count);
}

int	validate_player_count(char **map_lines, int map_line_count)
{
	int	player_count;

	player_count = count_players(map_lines, map_line_count);
	if (player_count == 0)
	{
		ft_putendl_fd("Error: No player on the map", 2);
		return (0);
	}
	if (player_count > 1)
	{
		ft_putendl_fd("Error: Multiple players on the map", 2);
		return (0);
	}
	return (1);
}

void	set_player(t_game *game, char direction, int x, int y)
{
	game->player.x_pos = x + 0.5;
	game->player.y_pos = y + 0.5;
	if (direction == 'N')
		game->player.orientation = 0;
	else if (direction == 'S')
		game->player.orientation = 180;
	else if (direction == 'E')
		game->player.orientation = 90;
	else if (direction == 'W')
		game->player.orientation = 270;
	game->map[y][x] = 0;
}

static int	get_max_columns(t_file_data *file_data)
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

static int	allocate_map(t_game *game, t_file_data *file_data, int max_cols)
{
	int	y;

	game->map = gc_malloc(sizeof(int *) * (file_data->map_line_count + 1));
	if (!game->map)
		return (0);
	game->map[file_data->map_line_count] = NULL;
	y = 0;
	while (y < file_data->map_line_count)
	{
		game->map[y] = gc_malloc(sizeof(int) * (max_cols + 1));
		if (!game->map[y])
			return (0);
		game->map[y][max_cols] = INT_MIN;
		y++;
	}
	return (1);
}

static int	map_char_to_value(t_game *game, char character, int row, int col)
{
	if (character == '0')
		return (0);
	else if (character == '1')
		return (1);
	else if (character == ' ')
		return (-1);
	else if (character == 'N' || character == 'S' || character == 'E'
		|| character == 'W')
	{
		set_player(game, character, col, row);
		return (0);
	}
	ft_putstr_fd("Error: Invalid character in map: ", 2);
	ft_putchar_fd(character, 2);
	ft_putchar_fd('\n', 2);
	return (-2);
}

static int	copy_map_lines(t_game *game, t_file_data *file_data,
		int max_columns)
{
	int	row;
	int	col;
	int	value;

	row = 0;
	while (row < file_data->map_line_count)
	{
		col = 0;
		while (file_data->map_lines[row][col] != '\0')
		{
			value = map_char_to_value(game, file_data->map_lines[row][col], row,
					col);
			if (value == -2)
				return (0);
			game->map[row][col] = value;
			col++;
		}
		while (col < max_columns)
			game->map[row][col++] = -1;
		row++;
	}
	return (1);
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

static t_image	*initialize_texture(void *mlx, char *file_path)
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

int	validate_content(t_game *game, char *content)
{
	t_file_data	*file_data;
	char		*current_content_ptr;
	char		*line;

	file_data = init_file_data();
	if (!content || !file_data)
		return (1);
	current_content_ptr = content;
	line = get_next_line(&current_content_ptr);
	while (line != NULL)
	{
		if (is_empty_line(line))
		{
			line = get_next_line(&current_content_ptr);
			continue ;
		}
		if (process_config_line(file_data, line) != 0)
			return (1);
		line = get_next_line(&current_content_ptr);
	}
	if (!validate_player_count(file_data->map_lines, file_data->map_line_count))
		return (1);
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
