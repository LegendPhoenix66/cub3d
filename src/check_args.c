/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:32:27 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/09 11:50:16 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_args(int argc, char **argv)
{
	size_t	len;
	char	*file_name;

	if (argc != 2)
	{
		printf("Error\nExpected 1 arguments, received %d\n", argc - 1);
		exit(1);
	}
	file_name = ft_strrchr(argv[1], '/');
	if (file_name)
		file_name++;
	else
		file_name = argv[1];
	len = ft_strlen(file_name);
	if (len < 4 || ft_strncmp(file_name + len - 4, ".ber", 4))
	{
		printf("Error\nFile extension should be '.ber'\n");
		exit(1);
	}
	else if (len == 4)
	{
		printf("Error\nFile name should not be empty\n");
		exit(1);
	}
}
