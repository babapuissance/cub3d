/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:00:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 18:00:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_player_direction_north(t_player *player)
{
	t_direction	dir;

	dir.dirx = 0;
	dir.diry = -1;
	dir.planex = 0.888;
	dir.yaw = -M_PI / 2;
	set_player_direction(player, dir);
}

void	set_player_direction_south(t_player *player)
{
	t_direction	dir;

	dir.dirx = 0;
	dir.diry = 1;
	dir.planex = -0.888;
	dir.yaw = M_PI / 2;
	set_player_direction(player, dir);
}

void	set_player_direction_east(t_player *player)
{
	t_direction	dir;

	dir.dirx = 1;
	dir.diry = 0;
	dir.planex = 0;
	dir.yaw = 0;
	set_player_direction(player, dir);
}

void	set_player_direction_west(t_player *player)
{
	t_direction	dir;

	dir.dirx = -1;
	dir.diry = 0;
	dir.planex = 0;
	dir.yaw = M_PI;
	set_player_direction(player, dir);
}
