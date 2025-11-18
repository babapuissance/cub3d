/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:05:31 by nbariol-          #+#    #+#             */
/*   Updated: 2025/11/18 13:51:07 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	read_map_loop1(t_cub *data, char *line, size_t *i, size_t *j)
{
	size_t	len;

	if (!line)
		return (0);
	data->map->map = ft_strjoin_free(data->map->map, line, 1);
	if (!data->map->map)
		return (0);
	len = ft_strlen(line);
	if (len > *j)
		*j = len;
	(*i)++;
	return (1);
}

static int	is_valid_trailing_line(char *line)
{
	size_t	k;

	k = 0;
	while (line[k])
	{
		if (line[k] != ' ' && line[k] != '\t' && line[k] != '\n'
			&& line[k] != '1' && line[k] != '0')
			return (0);
		k++;
	}
	return (1);
}

static int	read_map_loop2(char *line, int fd)
{
	while (line != NULL)
	{
		if (!is_valid_trailing_line(line))
		{
			cleanup_remaining_lines(fd);
			free(line);
			printf("Map is not last in the .cub file");
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	read_map_content(t_cub *data, int fd)
{
	char	*line;
	size_t	i;
	size_t	j;

	line = get_next_line(fd);
	i = 1;
	j = 0;
	if (data->map->map)
		j = ft_strlen(data->map->map);
	while (line && !is_first_or_last_line_valid(line))
	{
		if (!read_map_loop1(data, line, &i, &j))
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	if (line && !read_map_loop1(data, line, &i, &j))
		return (0);
	data->map->height = i;
	data->map->width = j;
	free(line);
	line = get_next_line(fd);
	return (read_map_loop2(line, fd));
}

int	cleanup_remaining_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (1);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
