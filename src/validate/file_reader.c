/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:10:37 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/23 18:10:37 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	append_buffer(char **content, const char *buffer, size_t bytes_read,
		size_t *total_size)
{
	char	*new_content;

	new_content = gc_realloc(*content, *total_size + bytes_read + 1);
	if (!new_content)
		return (1);
	*content = new_content;
	ft_memcpy(*content + *total_size, buffer, bytes_read);
	*total_size += bytes_read;
	(*content)[*total_size] = '\0';
	return (0);
}

ssize_t	read_and_process(int fd, char *buffer, char **content,
		size_t *total_size)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, 1024);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (append_buffer(content, buffer, bytes_read, total_size) == 1)
			return (handle_error("Error: Memory allocation failed"));
		bytes_read = read(fd, buffer, 1024);
	}
	return (bytes_read);
}

int	read_file_content(int fd, char **content)
{
	char	*buffer;
	size_t	total_size;
	ssize_t	read_status;

	total_size = 0;
	buffer = gc_malloc(1025);
	if (!buffer)
		return (handle_error("Error: Memory allocation failed"));
	read_status = read_and_process(fd, buffer, content, &total_size);
	if (read_status == -1)
		return (handle_error("Error: Failed to read the file"));
	return (0);
}

int	open_file(const char *file, char **content)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error: Could not open file", 2);
		return (1);
	}
	*content = gc_malloc(1);
	if (!*content)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		close(fd);
		return (1);
	}
	(*content)[0] = '\0';
	if (read_file_content(fd, content) == 1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

char	*get_next_line(char **content_ptr)
{
	char	*line_start;
	char	*line_end;
	char	*line;

	if (!*content_ptr || **content_ptr == '\0')
		return (NULL);
	line_start = *content_ptr;
	line_end = ft_strchr(line_start, '\n');
	if (line_end)
	{
		line = gc_malloc(line_end - line_start + 1);
		if (!line)
			return (NULL);
		ft_memcpy(line, line_start, line_end - line_start);
		line[line_end - line_start] = '\0';
		*content_ptr = line_end + 1;
	}
	else
	{
		line = gc_strdup(line_start);
		if (!line)
			return (NULL);
		*content_ptr = NULL;
	}
	return (line);
}
