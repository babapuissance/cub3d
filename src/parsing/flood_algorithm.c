/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_algorithm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:44:39 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:48:25 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool		validate_map_in_single_pass(t_cub *data, char **map);

char	**copy_map(char **original, int height)
{
	char	**duplicate;
	int		row;

	duplicate = malloc(sizeof(char *) * (height + 1));
	if (!duplicate)
		return (NULL);
	row = 0;
	while (row < height && original[row])
	{
		duplicate[row] = ft_strdup(original[row]);
		if (!duplicate[row])
		{
			while (--row >= 0)
				free(duplicate[row]);
			free(duplicate);
			return (NULL);
		}
		row++;
	}
	duplicate[row] = NULL;
	return (duplicate);
}

void	free_map_copy(char **map_copy, int height)
{
	int	row;

	if (!map_copy)
		return ;
	row = 0;
	while (row < height)
	{
		free(map_copy[row]);
		row++;
	}
	free(map_copy);
}

static void	mark_error(char **map)
{
	if (map && map[0])
		map[0][0] = 'E';
}

static int	check_bounds(char **map, int x, int y, int height)
{
	if (y < 0 || y >= height || x < 0)
		return (mark_error(map), 1);
	if (!map[y] || x >= (int)ft_strlen(map[y]))
		return (mark_error(map), 1);
	return (0);
}

void	flood_fill(char **map_copy, int x, int y, int height)
{
	if (check_bounds(map_copy, x, y, height))
		return ;
	if (map_copy[y][x] == ' ' || map_copy[y][x] == '1' || map_copy[y][x] == 'X')
	{
		if (map_copy[y][x] == ' ')
			mark_error(map_copy);
		return ;
	}
	if (!is_walkable(map_copy[y][x]))
		return ;
	map_copy[y][x] = 'X';
	flood_fill(map_copy, x + 1, y, height);
	flood_fill(map_copy, x - 1, y, height);
	flood_fill(map_copy, x, y + 1, height);
	flood_fill(map_copy, x, y - 1, height);
}

bool	check_map_borders_after_flood(char **map_copy, int height)
{
	(void)height;
	if (map_copy && map_copy[0] && map_copy[0][0] == 'E')
		return (false);
	return (true);
}

bool	flood_fill_test(t_cub *data, char **map)
{
	char	**map_copy;
	int		x;
	int		y;
				bool result;

	if (!validate_map_in_single_pass(data, map))
		return (false);
	map_copy = copy_map(map, data->map->height);
	if (!map_copy)
		return (false);
	y = 0;
	while (y < data->map->height && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player_character(map[y][x]))
			{
				flood_fill(map_copy, x, y, data->map->height);
				result = check_map_borders_after_flood(map_copy,
						data->map->height);
				free_map_copy(map_copy, data->map->height);
				return (result);
			}
			x++;
		}
		y++;
	}
	free_map_copy(map_copy, data->map->height);
	return (false);
}
