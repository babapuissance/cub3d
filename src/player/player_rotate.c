/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:13 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:49:07 by sle-bail         ###   ########.fr       */
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
