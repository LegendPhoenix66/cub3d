/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ueharakeiji <ueharakeiji@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:52:52 by ueharakeiji       #+#    #+#             */
/*   Updated: 2025/02/17 13:04:35 by ueharakeiji      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_row_length(t_game *game, int row)
{
	int	len;

	len = 0;
	while (game->map[row][len] != INT_MIN)
		len++;
	return (len);
}

int	validate_map_closed(t_game *game)
{
	int	row;
	int	col;
	int	len;
	int	len_up;
	int	len_down;

	row = 0;
	while (game->map[row])
	{
		len = get_row_length(game, row);
		col = 0;
		while (col < len)
		{
			if (game->map[row][col] == 0)
			{
				if (col - 1 < 0)
					return (0);
				if (col + 1 >= len)
					return (0);
				if (row - 1 < 0)
					return (0);
				len_up = get_row_length(game, row - 1);
				if (col >= len_up)
					return (0);
				if (game->map[row + 1] == NULL)
					return (0);
				len_down = get_row_length(game, row + 1);
				if (col >= len_down)
					return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}
