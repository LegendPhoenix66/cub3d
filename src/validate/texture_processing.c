/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:10:37 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 18:10:37 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
