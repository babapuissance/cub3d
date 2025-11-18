/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:32 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:49:19 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_texture	*get_horizontal_wall_texture(t_cub *game, t_ray *r)
{
	if (r->dirx > 0)
		return (game->we_texture_img);
	return (game->ea_texture_img);
}

static t_texture	*get_vertical_wall_texture(t_cub *game, t_ray *r)
{
	if (r->diry > 0)
		return (game->no_texture_img);
	return (game->so_texture_img);
}

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

static bool	should_flip_texture(t_ray *r)
{
	if (r->side == 0 && r->dirx < 0)
		return (true);
	if (r->side == 1 && r->diry > 0)
		return (true);
	return (false);
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

static int	clamp_coordinate(int coord, int max_value)
{
	if (coord < 0)
		return (0);
	if (coord >= max_value)
		return (max_value - 1);
	return (coord);
}

static int	compute_pixel_offset(t_texture *tex, int x, int y)
{
	return (y * tex->line_length + x * (tex->bits_per_pixel / 8));
}

int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	int	safe_x;
	int	safe_y;
	int	offset;

	safe_x = clamp_coordinate(tex_x, texture->width);
	safe_y = clamp_coordinate(tex_y, texture->height);
	offset = compute_pixel_offset(texture, safe_x, safe_y);
	return (*(int *)(texture->addr + offset));
}
