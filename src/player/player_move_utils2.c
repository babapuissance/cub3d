/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:35:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 19:35:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_position_within_map_bounds(double x, double y, t_map *map)
{
	return (x >= 0 && x < map->width && y >= 0 && y < map->height);
}

bool	is_tile_walkable(char tile_char)
{
	return (tile_char == '0' || tile_char == '6'
		|| is_player_character(tile_char));
}
