/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:10:37 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 18:10:37 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
