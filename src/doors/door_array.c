/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:42:57 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:47:10 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_door_orient	detect_door_orient(char door_char)
{
	if (door_char == 'D')
		return (DOOR_Y);
	if (door_char == 'F')
		return (DOOR_X);
	return (DOOR_Y);
}

static int	count_doors(t_cub *data)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (is_door_character(data->map->map_tab[y][x]))
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int	fill_doors_array(t_cub *data)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (is_door_character(data->map->map_tab[y][x]))
			{
				data->doors[count].i = x;
				data->doors[count].j = y;
				data->doors[count].orient = detect_door_orient(data->map->map_tab[y][x]);
				data->doors[count].is_closed = 1;
				count++;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	init_doors(t_cub *data)
{
	int	count;

	count = count_doors(data);
	if (count == 0)
	{
		data->doors = NULL;
		data->door_count = 0;
		return (1);
	}
	data->doors = malloc(sizeof(t_door) * count);
	if (!data->doors)
		return (0);
	data->door_count = count;
	return (fill_doors_array(data));
}
