/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:28 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/20 20:10:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	raycast_init(int x, t_player *player, t_ray *ray, double camera_x)
{
	(void)x;
	reset_ray_parameters(ray);
	setup_ray_direction_cached(camera_x, player, ray);
	ray->mapx = (int)player->pos_x;
	ray->mapy = (int)player->pos_y;
	calculate_delta_distances(ray);
}

void	dda_init(t_ray *ray, t_player *player)
{
	configure_horizontal_step(ray, player);
	configure_vertical_step(ray, player);
}

void	exec_dda(t_cub *data, t_ray *ray, int hit)
{
	char	tile;

	while (!hit)
	{
		advance_ray_in_grid(ray);
		if (is_grid_position_out_of_bounds(ray, data))
		{
			ray->wall_distance = 1e30;
			return ;
		}
		tile = data->map->map_tab[ray->mapy][ray->mapx];
		if (is_wall_tile(tile))
			hit = 1;
		else if (is_door_character(tile))
		{
			continue ;
		}
	}
}

static void	determine_screen_draw_limits(t_ray *r, t_cub *game)
{
	r->draw_start = -(r->line_height) / 2 + game->w_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + game->w_height / 2;
	if (r->draw_end >= game->w_height)
		r->draw_end = game->w_height - 1;
}

void	line_height(t_ray *ray, t_player *player, t_cub *data)
{
	ray->wall_distance = compute_perpendicular_distance(ray);
	ray->line_height = (int)(data->w_height / ray->wall_distance);
	determine_screen_draw_limits(ray, data);
	calculate_wall_intersection_point(ray, player);
}
