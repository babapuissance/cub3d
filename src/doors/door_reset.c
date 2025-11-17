/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 09:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/06 10:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	reset_door_states(t_cub *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
			data->door_state[y][x++] = '0';
		y++;
	}
	y = 0;
	while (y < data->door_count)
		data->doors[y++].is_closed = 1;
}

static void	reset_mob_position(t_cub *data)
{
	if (data->mob)
	{
		data->mob->x = data->mob_spawn_x;
		data->mob->y = data->mob_spawn_y;
	}
}

void	trigger_victory(t_cub *data)
{
	long	now;

	if (!data)
		return ;
	if (data->game_state == GAME_PLAYING)
	{
		now = now_ms();
		data->game_state = GAME_WON;
		data->game_end_time = now;
		data->win_display_until_ms = now + 5000;
	}
}

void	reset_game(t_cub *data)
{
	if (!data)
		return ;
	reset_door_states(data);
	set_player_pos(data);
	player_init(data);
	reset_mob_position(data);
	data->game_state = GAME_PLAYING;
}
