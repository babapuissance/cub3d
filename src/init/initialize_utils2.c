/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:43:53 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:48:05 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <time.h>

static int	init_cache_buffers(t_cub *data)
{
	data->camera_x_cache = malloc(sizeof(double) * WIDTH);
	if (!data->camera_x_cache)
		return (0);
	data->z_buffer = malloc(sizeof(double) * WIDTH);
	return (data->z_buffer != NULL);
}

static void	init_speed_and_sprite(t_cub *data)
{
	data->movespeed = MOVESPEED * ((double)WIDTH / 800.0);
	data->rotationspeed = ROTATIONSPEED * ((double)WIDTH / 800.0);
	data->mob_speed = MOB_SPEED;
	data->sprite = NULL;
	data->sprite_texture = NULL;
	data->screamer_texture = NULL;
	data->mob_spawn_x = 0.0;
	data->mob_spawn_y = 0.0;
}

static void	init_ui_state(t_cub *data)
{
	data->menu_texture = NULL;
	data->start_button = NULL;
	data->win_texture = NULL;
	data->win_display_until_ms = 0;
	data->gameover_texture = NULL;
	data->gameover_display_until_ms = 0;
	data->event_state = 0;
	data->event_next_ms = 0;
	data->blackout_until_ms = 0;
	data->monster_prev_visible = 0;
	data->event_cooldown_until_ms = 0;
	data->game_state = GAME_MENU;
	data->game_end_time = 0;
}

int	data_init(t_cub *data)
{
	if (!data)
		return (0);
	init_mlx_pointers(data);
	init_texture_pointers(data);
	init_window_dimensions(data);
	if (!init_map_structure(data))
		return (0);
	if (!init_game_objects(data))
	{
		if (data->map && data->map->infos)
			free(data->map->infos);
		if (data->map)
			free(data->map);
		return (0);
	}
	if (!init_cache_buffers(data))
		return (0);
	init_speed_and_sprite(data);
	init_ui_state(data);
	return (1);
}

typedef struct s_direction
{
	double	dirx;
	double	diry;
	double	planex;
	double	yaw;
}			t_direction;

void	set_player_direction(t_player *player, t_direction dir)
{
	player->dirx = dir.dirx;
	player->diry = dir.diry;
	player->planex = dir.planex;
	player->planey = (dir.planex != 0) ? 0 : 0.888
		* (dir.diry != 0 ? dir.diry : 1);
	player->yaw = dir.yaw;
}

void	set_player_direction_north(t_player *player)
{
	t_direction	dir;

	dir = {0, -1, 0.888, -M_PI / 2};
	set_player_direction(player, dir);
}

void	set_player_direction_south(t_player *player)
{
	t_direction	dir;

	dir = {0, 1, -0.888, M_PI / 2};
	set_player_direction(player, dir);
}

void	set_player_direction_east(t_player *player)
{
	t_direction	dir;

	dir = {1, 0, 0, 0};
	set_player_direction(player, dir);
}

void	set_player_direction_west(t_player *player)
{
	t_direction	dir;

	dir = {-1, 0, 0, M_PI};
	set_player_direction(player, dir);
}
