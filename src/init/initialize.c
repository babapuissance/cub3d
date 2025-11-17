/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/10/29 10:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_player_movement(t_player *player)
{
	player->moving_x = 0;
	player->moving_y = 0;
	player->rotate = 0;
	player->capture_mouse = 0;
}

static void	set_player_direction_and_camera(t_player *player)
{
	switch (player->player_dir)
	{
		case 'N':
			set_player_direction_north(player);
			break ;
		case 'S':
			set_player_direction_south(player);
			break ;
		case 'E':
			set_player_direction_east(player);
			break ;
		case 'W':
			set_player_direction_west(player);
			break ;
	}
}

void	player_init(t_cub *data)
{
	if (!data || !data->player)
		return ;
	set_player_direction_and_camera(data->player);
	init_player_movement(data->player);
}

static int	check_init(int result, t_cub *data)
{
	if (result == 0)
		ft_close_window(data);
	return (result);
}

void	textures_and_colors_init(t_cub *data)
{
	if (north_texture(data) == 0 || west_texture(data) == 0
		|| south_texture(data) == 0 || east_texture(data) == 0
		|| floor_texture(data) == 0 || ceiling_texture(data) == 0)
		ft_close_window(data);
	check_init(door_texture_loader(data), data);
	check_init(init_door_state(data), data);
	check_init(init_doors(data), data);
	check_init(load_menu_texture(data), data);
	check_init(load_win_texture(data), data);
	check_init(load_gameover_texture(data), data);
}
