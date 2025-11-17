/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/03 12:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	move_in_direction(t_cub *cub, double dx, double dy)
{
	apply_movement_vector(cub, dx, dy);
}

static void	move_forward(t_cub *cub)
{
	move_in_direction(cub, cub->player->dirx, cub->player->diry);
}

static void	move_backward(t_cub *cub)
{
	move_in_direction(cub, -cub->player->dirx, -cub->player->diry);
}

static void	move_left(t_cub *cub)
{
	move_in_direction(cub, -cub->player->planex, -cub->player->planey);
}

static void	move_right(t_cub *cub)
{
	move_in_direction(cub, cub->player->planex, cub->player->planey);
}

void	move_player(t_cub *cub)
{
	if (cub->player->moving_y == 1)
		move_forward(cub);
	else if (cub->player->moving_y == -1)
		move_backward(cub);
	if (cub->player->moving_x == 1)
		move_right(cub);
	else if (cub->player->moving_x == -1)
		move_left(cub);
}

