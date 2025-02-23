/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:10:37 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 18:10:37 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
