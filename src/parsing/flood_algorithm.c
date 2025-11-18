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

bool	flood_fill_test(t_cub *data, char **map)
{
	if (!validate_map_in_single_pass(data, map))
		return (false);
	return (perform_flood_fill_validation(data, map));
}
