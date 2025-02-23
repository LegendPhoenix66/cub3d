/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:10:37 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 18:10:37 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
