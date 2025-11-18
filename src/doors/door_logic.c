/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:43:08 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:47:13 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_door_closed(t_cub *data, int mapx, int mapy)
{
	if (!data || !data->door_state)
		return (true);
	if (mapy < 0 || mapy >= data->map->height)
		return (true);
	if (mapx < 0 || mapx >= data->map->width)
		return (true);
	return (data->door_state[mapy][mapx] == '0');
}

static void	update_door_in_array(t_cub *data, int mapx, int mapy)
{
	int	i;

	if (!data->doors)
		return ;
	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].i == mapx && data->doors[i].j == mapy)
		{
			data->doors[i].is_closed = (data->door_state[mapy][mapx] == '0');
			break ;
		}
		i++;
	}
}

static void	toggle_door_at(t_cub *data, int mapx, int mapy)
{
	if (mapy < 0 || mapy >= data->map->height)
		return ;
	if (mapx < 0 || mapx >= data->map->width)
		return ;
	if (data->door_state[mapy][mapx] == '0')
		data->door_state[mapy][mapx] = '1';
	else
		data->door_state[mapy][mapx] = '0';
	update_door_in_array(data, mapx, mapy);
}

static int	distance_to_door(t_cub *data, int x, int y)
{
	double	dx;
	double	dy;
	double	dist;

	dx = data->player->pos_x - (x + 0.5);
	dy = data->player->pos_y - (y + 0.5);
	dist = sqrt(dx * dx + dy * dy);
	return (dist < 1.2);
}

void	toggle_door_state(t_cub *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (is_door_character(data->map->map_tab[y][x]))
			{
				if (distance_to_door(data, x, y))
					toggle_door_at(data, x, y);
			}
			x++;
		}
		y++;
	}
}

bool	check_all_doors_open(t_cub *data)
{
	int	i;

	if (!data || !data->doors || data->door_count == 0)
		return (false);
	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].is_closed == 1)
			return (false);
		i++;
	}
	return (true);
}
