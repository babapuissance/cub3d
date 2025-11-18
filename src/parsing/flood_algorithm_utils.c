/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_algorithm_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:10:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 19:10:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

bool	check_map_borders_after_flood(char **map_copy, int height)
{
	(void)height;
	if (map_copy && map_copy[0] && map_copy[0][0] == 'E')
		return (false);
	return (true);
}

static bool	process_flood_fill(char **map, char **map_copy, t_cub *data)
{
	int		x;
	int		y;
	bool	result;

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
				return (result);
			}
			x++;
		}
		y++;
	}
	return (false);
}

bool	perform_flood_fill_validation(t_cub *data, char **map)
{
	char	**map_copy;
	bool	result;

	map_copy = copy_map(map, data->map->height);
	if (!map_copy)
		return (false);
	result = process_flood_fill(map, map_copy, data);
	free_map_copy(map_copy, data->map->height);
	return (result);
}
