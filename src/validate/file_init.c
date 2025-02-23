/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:07:27 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 18:12:11 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
