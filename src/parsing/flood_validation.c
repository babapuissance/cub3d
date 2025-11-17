/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/10/31 14:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_walkable(char c)
{
	return (c == '0' || c == '6' || c == 'D' || c == 'F'
		|| is_player_character(c));
}

static bool	is_valid_map_character(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == '6' || c == '3'
		|| c == 'D' || c == 'F'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == '\n' || c == '\0');
}

static bool	validate_door_d(char **map, int x, int y, int height)
{
	if (y == 0 || y >= height - 1)
		return (false);
	return (map[y - 1][x] == '1' && map[y + 1][x] == '1');
}

static bool	validate_door_f(char **map, int x, int y, int width)
{
	if (x == 0 || x >= width - 1)
		return (false);
	return (map[y][x - 1] == '1' && map[y][x + 1] == '1');
}

bool	validate_map_in_single_pass(t_cub *data, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map->height && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_map_character(map[y][x]))
				return (false);
			if (map[y][x] == 'D'
				&& !validate_door_d(map, x, y, data->map->height))
				return (false);
			if (map[y][x] == 'F'
				&& !validate_door_f(map, x, y, data->map->width))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}
