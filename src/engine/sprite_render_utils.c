/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:45:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 17:45:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_sprite_params(int *params, int start, int height, int left)
{
	params[0] = start;
	params[1] = height;
	params[2] = left;
	params[3] = HEIGHT / 2 + height / 2;
}

void	draw_sprite_loop(t_cub *data, int params[5], double tr_y)
{
	int	x;
	int	end;

	x = params[2];
	end = params[2] + params[4];
	while (x < end && x < WIDTH)
	{
		if (x >= 0)
			draw_sprite_column(data, x, params, tr_y);
		x++;
	}
}
