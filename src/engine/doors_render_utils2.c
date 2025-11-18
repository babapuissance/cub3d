/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_render_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:15:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 17:15:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	compute_door_y(t_cub *g, t_door *door, t_ray_calc *calc)
{
	if (fabs(calc->rx) < FLOAT_EPSILON)
		return (0);
	calc->t = (door->i - g->player->pos_x) / calc->rx;
	if (calc->t <= 0)
		return (0);
	calc->u = g->player->pos_y + calc->t * calc->ry - door->j;
	return (1);
}

static int	compute_door_x(t_cub *g, t_door *door, t_ray_calc *calc)
{
	if (fabs(calc->ry) < FLOAT_EPSILON)
		return (0);
	calc->t = (door->j - g->player->pos_y) / calc->ry;
	if (calc->t <= 0)
		return (0);
	calc->u = g->player->pos_x + calc->t * calc->rx - door->i;
	return (1);
}

t_ray_result	compute_ray_intersection(t_cub *g, t_door *door,
		double camera_x)
{
	t_ray_result	result;
	t_ray_calc		calc;

	result.hit = 0;
	calc.rx = g->player->dirx + g->player->planex * camera_x;
	calc.ry = g->player->diry + g->player->planey * camera_x;
	if (door->orient == DOOR_Y)
	{
		if (!compute_door_y(g, door, &calc))
			return (result);
	}
	else
	{
		if (!compute_door_x(g, door, &calc))
			return (result);
	}
	if (calc.u < 0.0 || calc.u > 1.0)
		return (result);
	result.t = calc.t;
	result.u = calc.u;
	result.hit = 1;
	return (result);
}
