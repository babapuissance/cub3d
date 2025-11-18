/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary_checker_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:00:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 19:00:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
