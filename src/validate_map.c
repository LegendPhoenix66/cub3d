/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:55:03 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/20 11:47:27 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_cell(int **map, int row, int col)
{
	if (map[row][col] != 0)
		return (0);
	if (row == 0 || map[row + 1] == NULL)
		return (1);
	if (col == 0 || map[row][col + 1] == INT_MIN)
		return (1);
	if (map[row + 1][col] == -1 || map[row - 1][col] == -1
	|| map[row][col + 1] == -1 || map[row][col - 1] == -1
	|| map[row + 1][col + 1] == -1 || map[row + 1][col - 1] == -1
	|| map[row - 1][col + 1] == -1 || map[row - 1][col - 1] == -1)
		return (1);
	return (0);
}

int	is_map_valid(int **map)
{
	int	row;
	int	col;

	row = 0;
	while (map[row] != NULL)
	{
		col = 0;
		while (map[row][col] != INT_MIN)
		{
			if (check_cell(map, row, col) != 0)
			{
				printf("Error: map is not valid\n");
				printf("Row: %d, Col: %d\n", row, col);
				return (1);
			}
			col++;
		}
		row++;
	}
	return (0);
}
