/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:05:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 20:05:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	determine_screen_draw_limits(t_ray *r, t_cub *game)
{
	r->draw_start = -(r->line_height) / 2 + game->w_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + game->w_height / 2;
	if (r->draw_end >= game->w_height)
		r->draw_end = game->w_height - 1;
}
