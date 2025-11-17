/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary_checker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/10/31 12:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_valid_position(int x, int y, char **map, int map_height)
{
	if (y < 0 || y >= map_height)
		return (false);
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (false);
	return (true);
}

bool	is_empty_space_at(int x, int y, char **map, int map_height)
{
	if (!is_valid_position(x, y, map, map_height))
		return (false);
	return (map[y][x] == ' ');
}

bool	check_adjacent_horizontal(int x, int y, char **map, int height)
{
	if (is_empty_space_at(x - 1, y, map, height))
		return (false);
	if (is_empty_space_at(x + 1, y, map, height))
		return (false);
	return (true);
}

bool	check_adjacent_vertical(int x, int y, char **map, int height)
{
	if (is_empty_space_at(x, y - 1, map, height))
		return (false);
	if (is_empty_space_at(x, y + 1, map, height))
		return (false);
	return (true);
}

bool	check_diagonal_neighbors(int x, int y, char **map, int height)
{
	if (is_empty_space_at(x - 1, y - 1, map, height))
		return (false);
	if (is_empty_space_at(x + 1, y - 1, map, height))
		return (false);
	if (is_empty_space_at(x - 1, y + 1, map, height))
		return (false);
	if (is_empty_space_at(x + 1, y + 1, map, height))
		return (false);
	return (true);
}

bool	check_walls(t_cub *cub, char **map, int x, int y)
{
	int	height;

	height = cub->map->height;
	if (!check_adjacent_horizontal(x, y, map, height))
		return (false);
	if (!check_adjacent_vertical(x, y, map, height))
		return (false);
	if (!check_diagonal_neighbors(x, y, map, height))
		return (false);
	return (true);
}

bool	is_first_or_last_line_valid(char *line)
{
	int	idx;

	if (!line || is_line_empty(line))
		return (false);
	idx = 0;
	while (line[idx])
	{
		if (line[idx] != '1' && line[idx] != ' ' && line[idx] != '\n')
			return (false);
		idx++;
	}
	return (true);
}
