/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:10:37 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 18:10:37 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	allocate_map(t_game *game, t_file_data *file_data, int max_cols)
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

int	map_char_to_value(t_game *game, char character, int row, int col)
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

int	copy_map_lines(t_game *game, t_file_data *file_data, int max_columns)
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
