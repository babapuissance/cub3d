/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_locator.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/10/31 16:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_player_character(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	count_players_in_map(char *map, t_cub *data)
{
	int	count;
	int	pos;

	count = 0;
	pos = 0;
	while (map[pos])
	{
		if (is_player_character(map[pos]))
		{
			data->player->player_dir = map[pos];
			count++;
		}
		pos++;
	}
	return (count);
}

bool	pos_nb_checker(char *map, t_cub *data)
{
	int	player_count;

	player_count = count_players_in_map(map, data);
	return (player_count == 1);
}

static bool	find_player_in_grid(char **grid, int *x, int *y)
{
	int	row;
	int	col;

	row = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col])
		{
			if (is_player_character(grid[row][col]))
			{
				*x = col;
				*y = row;
				return (true);
			}
			col++;
		}
		row++;
	}
	return (false);
}

void	set_player_pos(t_cub *data)
{
	int	player_x;
	int	player_y;

	if (find_player_in_grid(data->map->map_tab, &player_x, &player_y))
	{
		data->player->pos_x = (double)player_x + 0.5;
		data->player->pos_y = (double)player_y + 0.5;
	}
}
