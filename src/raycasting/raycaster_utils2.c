/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:32 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/20 20:17:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_texture	*select_texture(t_cub *data, t_ray *ray)
{
	char	tile;

	tile = data->map->map_tab[ray->mapy][ray->mapx];
	if (is_door_character(tile))
		return (NULL);
	if (ray->side == 0)
		return (get_horizontal_wall_texture(data, ray));
	return (get_vertical_wall_texture(data, ray));
}

void	calculate_texture_coordinates(t_ray *ray, t_texture *texture,
		int *tex_x)
{
	int	raw_coord;

	raw_coord = (int)(ray->wall_x * (double)texture->width);
	if (should_flip_texture(ray))
		*tex_x = texture->width - raw_coord - 1;
	else
		*tex_x = raw_coord;
}

int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	int	safe_x;
	int	safe_y;
	int	offset;

	safe_x = tex_x;
	if (safe_x < 0)
		safe_x = 0;
	if (safe_x >= texture->width)
		safe_x = texture->width - 1;
	safe_y = tex_y;
	if (safe_y < 0)
		safe_y = 0;
	if (safe_y >= texture->height)
		safe_y = texture->height - 1;
	offset = safe_y * texture->line_length + safe_x
		* (texture->bits_per_pixel / 8);
	return (*(int *)(texture->addr + offset));
}
