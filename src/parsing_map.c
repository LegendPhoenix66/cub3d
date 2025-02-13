/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:20:32 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/13 00:59:28 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	**parsing_map(char **map, int map_line_count)
{
	int i;
	int j;
	int row_len;
	int **int_map;

	int_map = gc_malloc(sizeof(int *) * (map_line_count + 1));
	if (!int_map)
	{
		ft_putendl_fd("Error: Memory allocation failed in parsing_map", 2);
		exit(1);
	}

	i = 0;
	while (i < map_line_count)
	{
		row_len = ft_strlen(map[i]);
		int_map[i] = gc_malloc(sizeof(int) * (row_len + 1));
		if (!int_map[i])
		{
			ft_putendl_fd("Error: Memory allocation failed in parsing_map", 2);
			exit(1);
		}
		j = 0;
		while (j < row_len)
		{
			if (map[i][j] == '1')
				int_map[i][j] = 1;
			else
				int_map[i][j] = 0;
			j++;
		}
		int_map[i][j] = -1;
		i++;
	}
	int_map[i] = NULL;
	return (int_map);
}