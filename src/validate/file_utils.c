/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:10:37 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 18:10:37 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	handle_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (1);
}
