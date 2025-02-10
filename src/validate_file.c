/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:43:58 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/10 13:43:58 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(char *file, char **content)
{
	int		fd;
	char	*buffer;
	size_t	chunk_size;
	ssize_t	bytes_read;
	size_t	total_size;

	chunk_size = 1024;
	total_size = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nCould not open file\n");
		return (1);
	}
	*content = gc_malloc(1);
	if (!*content)
	{
		perror("Error\nMemory allocation failed\n");
		close(fd);
		return (1);
	}
	(*content)[0] = '\0';
	buffer = gc_malloc(chunk_size + 1);
	if (!buffer)
	{
		perror("Error\nMemory allocation failed\n");
		close(fd);
		return (1);
	}
	while ((bytes_read = read(fd, buffer, chunk_size)) > 0)
	{
		buffer[bytes_read] = '\0';
		*content = gc_realloc(*content, total_size + bytes_read + 1);
        if (!*content)
		{
			perror("Error\nMemory allocation failed\n");
			close(fd);
			return (1);
		}
		ft_memcpy(*content + total_size, buffer, bytes_read);
		total_size += bytes_read;
        (*content)[total_size] = '\0';
    }
	if (bytes_read == -1)
	{
		perror("Error\nFailed to read the file\n");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	is_file_valid(t_game *game, char *file)
{
    (void)game;
    char	*content;

	if (open_file(file, &content))
	{
		return (1);
	}
	printf("File Content:\n%s\n", content);
	return (0);
}
