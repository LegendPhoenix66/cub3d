/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhopp <lhopp@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:43:58 by lhopp             #+#    #+#             */
/*   Updated: 2025/02/10 18:43:33 by lhopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void print_file_data(t_file_data *file_data)
{
    printf("File Data:\n");
    printf("North Texture: %s\n", file_data->north_texture);
    printf("South Texture: %s\n", file_data->south_texture);
    printf("West Texture: %s\n", file_data->west_texture);
    printf("East Texture: %s\n", file_data->east_texture);
    printf("Floor Color: %s\n", file_data->floor_color_str);
    printf("Ceiling Color: %s\n", file_data->ceiling_color_str);
    printf("Map Lines:\n");
    for (int i = 0; i < file_data->map_line_count; i++) {
        printf("%s\n", file_data->map_lines[i]);
    }
    printf("Map Lines Count: %d\n", file_data->map_line_count);
}

int is_space(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int is_empty_line(const char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (!is_space(line[i])) {
            return (0); // Not empty
        }
    }
    return (1); // Empty
}

int process_texture_line(t_file_data *file_data, const char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0) {
        file_data->north_texture = gc_strdup(line + 3);
    } else if (ft_strncmp(line, "SO ", 3) == 0) {
        file_data->south_texture = gc_strdup(line + 3);
    } else if (ft_strncmp(line, "WE ", 3) == 0) {
        file_data->west_texture = gc_strdup(line + 3);
    } else if (ft_strncmp(line, "EA ", 3) == 0) {
        file_data->east_texture = gc_strdup(line + 3);
    } else {
        return (0);
    }
    return (1);
}

int process_color_line(t_file_data *file_data, const char *line)
{
    if (ft_strncmp(line, "F ", 2) == 0) {
        file_data->floor_color_str = gc_strdup(line + 2);
    } else if (ft_strncmp(line, "C ", 2) == 0) {
        file_data->ceiling_color_str = gc_strdup(line + 2);
    } else {
        return (0);
    }
    return (1);
}

int process_map_line(t_file_data *file_data, char *line)
{
    char **new_map_lines = gc_realloc(file_data->map_lines, sizeof(char*) * (file_data->map_line_count + 1));
    if (!new_map_lines) {
        return (-1);
    }
    file_data->map_lines = new_map_lines;
    file_data->map_lines[file_data->map_line_count] = line;
    file_data->map_line_count++;
    return (0);
}

void print_missing_config(t_file_data *file_data)
{
    if (!file_data->north_texture)
        perror("Error: Missing north texture (NO).\n");
    if (!file_data->south_texture)
        perror("Error: Missing south texture (SO).\n");
    if (!file_data->west_texture)
        perror("Error: Missing west texture (WE).\n");
    if (!file_data->east_texture)
        perror("Error: Missing east texture (EA).\n");
    if (!file_data->floor_color_str)
        perror("Error: Missing floor color (F).\n");
    if (!file_data->ceiling_color_str)
        perror("Error: Missing ceiling color (C).\n");
}

int is_config_complete(t_file_data *file_data)
{
    return (file_data->north_texture &&
            file_data->south_texture &&
            file_data->west_texture &&
            file_data->east_texture &&
            file_data->floor_color_str &&
            file_data->ceiling_color_str);
}

int process_config_line(t_file_data *file_data, char *line)
{
    char *value_start = line;
    while (is_space(*value_start))
        value_start++;

    if (process_texture_line(file_data, value_start)) {
        return (0);
    } else if (process_color_line(file_data, value_start)) {
        return (0);
    } else {
        if (!is_config_complete(file_data)) {
            print_missing_config(file_data);
            return (1);
        }
        return (process_map_line(file_data, line));
    }
}

char *get_next_line(char **content_ptr)
{
    if (!*content_ptr || **content_ptr == '\0')
        return (NULL);

    char *line_start = *content_ptr;
    char *line_end = ft_strchr(line_start, '\n');
    char *line = NULL;

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


int validate_content(t_game *game, char *content)
{
    (void)game;
    if (!content)
        return (1);

    t_file_data *file_data = init_file_data();
    if (!file_data)
        return (1);

    char *current_content_ptr = content;
    char *line;

    while ((line = get_next_line(&current_content_ptr)) != NULL)
    {
        if (is_empty_line(line)) {
            continue;
        }

        if (process_config_line(file_data, line) != 0) {
            return (1);
        }
    }

    print_file_data(file_data);
    return (0);
}

int	is_file_valid(t_game *game, char *file)
{
    char	*content;

	if (open_file(file, &content) != 0)
	{
		return (1);
	}
    if (validate_content(game, content) != 0)
    {
        return (1);
    }
	return (0);
}
