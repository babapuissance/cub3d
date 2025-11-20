/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:22:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/20 20:22:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	raycasting(t_cub *data)
{
	int			screen_column;
	t_texture	*wall_tex;
	int			texture_x_coord;

	screen_column = 0;
	while (screen_column < WIDTH)
	{
		cast_single_ray(data, screen_column);
		wall_tex = select_texture(data, data->ray);
		calculate_texture_coordinates(data->ray, wall_tex, &texture_x_coord);
		draw_column(data, screen_column, wall_tex, texture_x_coord);
		screen_column++;
	}
	return (0);
}
