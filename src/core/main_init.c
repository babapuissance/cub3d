/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:40:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 16:40:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	precalculate_camera_x(t_cub *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		data->camera_x_cache[x] = 2.0 * x / (double)WIDTH - 1.0;
		x++;
	}
}

void	initialize_game(t_cub *data)
{
	player_init(data);
	initialize_mlx(data);
	textures_and_colors_init(data);
	init_sprite(data);
	init_mob(data);
	precalculate_camera_x(data);
}

void	run_game(t_cub *data)
{
	raycasting(data);
	events_handling(data);
	mlx_loop(data->mlx);
}
