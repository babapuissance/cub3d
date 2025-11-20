/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_rendering_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:25:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/20 20:30:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_tiled_texture_color(t_texture *tex, double x, double y)
{
	int	tex_x;
	int	tex_y;
	int	size;

	x = fmod(x, 1.0);
	y = fmod(y, 1.0);
	if (x < 0)
		x += 1.0;
	if (y < 0)
		y += 1.0;
	size = tex->width;
	if (tex->height < size)
		size = tex->height;
	tex_x = (int)(x * (size - 1)) % size;
	tex_y = (int)(y * (size - 1)) % size;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	return (get_texture_color(tex, tex_x, tex_y));
}

int	get_floor_texture_color(t_cub *game, double floor_x, double floor_y)
{
	return (get_tiled_texture_color(game->floor_texture_img, floor_x, floor_y));
}

int	get_ceiling_texture_color(t_cub *game, double ceil_x, double ceil_y)
{
	return (get_tiled_texture_color(game->ceiling_texture_img, ceil_x, ceil_y));
}
