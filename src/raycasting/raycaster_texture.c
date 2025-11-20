/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:00:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/20 21:00:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_texture	*get_horizontal_wall_texture(t_cub *game, t_ray *r)
{
	if (r->dirx > 0)
		return (game->we_texture_img);
	return (game->ea_texture_img);
}

t_texture	*get_vertical_wall_texture(t_cub *game, t_ray *r)
{
	if (r->diry > 0)
		return (game->no_texture_img);
	return (game->so_texture_img);
}

bool	should_flip_texture(t_ray *r)
{
	if (r->side == 0 && r->dirx < 0)
		return (true);
	if (r->side == 1 && r->diry > 0)
		return (true);
	return (false);
}
