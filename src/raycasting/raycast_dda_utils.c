/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:05:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/20 20:05:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_grid_position_out_of_bounds(t_ray *r, t_cub *game)
{
	return (r->mapy < 0 || r->mapx < 0 || r->mapy >= game->map->height
		|| r->mapx >= game->map->width);
}

bool	is_wall_tile(char tile)
{
	return (tile == '1' || tile == ' ');
}

void	advance_ray_in_grid(t_ray *r)
{
	if (r->sidedistx < r->sidedisty)
	{
		r->sidedistx += r->deltadistx;
		r->mapx += r->stepx;
		r->side = 0;
	}
	else
	{
		r->sidedisty += r->deltadisty;
		r->mapy += r->stepy;
		r->side = 1;
	}
}

double	compute_perpendicular_distance(t_ray *r)
{
	if (r->side == 0)
		return (r->sidedistx - r->deltadistx);
	return (r->sidedisty - r->deltadisty);
}

void	calculate_wall_intersection_point(t_ray *r, t_player *p)
{
	if (r->side == 0)
		r->wall_x = p->pos_y + r->wall_distance * r->diry;
	else
		r->wall_x = p->pos_x + r->wall_distance * r->dirx;
	r->wall_x -= floor(r->wall_x);
}
