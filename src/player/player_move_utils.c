/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:05 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:48:39 by sle-bail         ###   ########.fr       */
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

typedef struct s_door_check
{
	int		grid_x;
	int		grid_y;
	double	target_x;
	double	target_y;
}			t_door_check;

static bool	is_blocked_by_closed_door(t_cub *game, double current_x,
		t_door_check check)
{
	int		i;
	double	dx;
	double	dy;
	t_door	*door;

	dx = check.target_x - current_x;
	dy = check.target_y - game->player->pos_y;
	i = 0;
	while (i < game->door_count)
	{
		door = &game->doors[i];
		if (door->i == check.grid_x && door->j == check.grid_y
			&& door->is_closed)
		{
			if (door->orient == DOOR_Y && dx != 0)
				return (true);
			if (door->orient == DOOR_X && dy != 0)
				return (true);
		}
		i++;
	}
	return (false);
}

bool	can_move_to_coordinates(t_cub *game, double target_x, double target_y)
{
	int				grid_x;
	int				grid_y;
	char			tile;
	t_door_check	check;

	if (!is_position_within_map_bounds(target_x, target_y, game->map))
		return (false);
	grid_x = (int)target_x;
	grid_y = (int)target_y;
	tile = game->map->map_tab[grid_y][grid_x];
	if (!is_tile_walkable(tile))
	{
		if (!is_door_character(tile))
			return (false);
		{
			check = {grid_x, grid_y, target_x, target_y};
			if (is_blocked_by_closed_door(game, game->player->pos_x, check))
				return (false);
		}
	}
	return (true);
}

void	attempt_position_update(t_cub *game, double new_x, double new_y)
{
	double	current_x;
	double	current_y;

	current_x = game->player->pos_x;
	current_y = game->player->pos_y;
	if (can_move_to_coordinates(game, current_x, new_y))
		game->player->pos_y = new_y;
	if (can_move_to_coordinates(game, new_x, current_y))
		game->player->pos_x = new_x;
}

void	apply_movement_vector(t_cub *game, double dx, double dy)
{
	double	velocity;
	double	target_x;
	double	target_y;

	velocity = game->movespeed;
	target_x = game->player->pos_x + dx * velocity;
	target_y = game->player->pos_y + dy * velocity;
	attempt_position_update(game, target_x, target_y);
}
