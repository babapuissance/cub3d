/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/04 10:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	rotate_right(t_cub *cub)
{
	execute_rotation(cub, -cub->rotationspeed);
}

static void	rotate_left(t_cub *cub)
{
	execute_rotation(cub, cub->rotationspeed);
}

void	rotate_player(t_cub *data)
{
	if (data->player->rotate == 1)
		rotate_right(data);
	else if (data->player->rotate == -1)
		rotate_left(data);
}
