/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:00:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/20 20:00:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	reset_ray_parameters(t_ray *ray_ptr)
{
	ray_ptr->camerax = 0;
	ray_ptr->dirx = 0;
	ray_ptr->diry = 0;
	ray_ptr->mapx = 0;
	ray_ptr->mapy = 0;
	ray_ptr->stepx = 0;
	ray_ptr->stepy = 0;
	ray_ptr->sidedistx = 0;
	ray_ptr->sidedisty = 0;
	ray_ptr->deltadistx = 0;
	ray_ptr->deltadisty = 0;
	ray_ptr->wall_distance = 0;
	ray_ptr->wall_x = 0;
	ray_ptr->side = 0;
	ray_ptr->line_height = 0;
	ray_ptr->draw_start = 0;
	ray_ptr->draw_end = 0;
}

void	setup_ray_direction_cached(double camera_x, t_player *plr, t_ray *r)
{
	r->camerax = camera_x;
	r->dirx = plr->dirx + plr->planex * camera_x;
	r->diry = plr->diry + plr->planey * camera_x;
}

void	calculate_delta_distances(t_ray *ray_data)
{
	ray_data->deltadistx = fabs(1 / ray_data->dirx);
	ray_data->deltadisty = fabs(1 / ray_data->diry);
}

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
