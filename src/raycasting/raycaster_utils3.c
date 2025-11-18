/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:00:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 20:00:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	configure_horizontal_step(t_ray *r, t_player *p)
{
	if (r->dirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (p->pos_x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - p->pos_x) * r->deltadistx;
	}
}

void	configure_vertical_step(t_ray *r, t_player *p)
{
	if (r->diry < 0)
	{
		r->stepy = -1;
		r->sidedisty = (p->pos_y - r->mapy) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - p->pos_y) * r->deltadisty;
	}
}

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
