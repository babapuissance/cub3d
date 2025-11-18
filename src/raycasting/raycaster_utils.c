/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:28 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:49:15 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	reset_ray_parameters(t_ray *ray_ptr)
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

static void	setup_ray_direction_cached(double camera_x, t_player *plr, t_ray *r)
{
	r->camerax = camera_x;
	r->dirx = plr->dirx + plr->planex * camera_x;
	r->diry = plr->diry + plr->planey * camera_x;
}

static void	calculate_delta_distances(t_ray *ray_data)
{
	ray_data->deltadistx = fabs(1 / ray_data->dirx);
	ray_data->deltadisty = fabs(1 / ray_data->diry);
}

void	raycast_init(int x, t_player *player, t_ray *ray, double camera_x)
{
	(void)x;
	reset_ray_parameters(ray);
	setup_ray_direction_cached(camera_x, player, ray);
	ray->mapx = (int)player->pos_x;
	ray->mapy = (int)player->pos_y;
	calculate_delta_distances(ray);
}

static void	configure_horizontal_step(t_ray *r, t_player *p)
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

static void	configure_vertical_step(t_ray *r, t_player *p)
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

void	dda_init(t_ray *ray, t_player *player)
{
	configure_horizontal_step(ray, player);
	configure_vertical_step(ray, player);
}

static bool	is_grid_position_out_of_bounds(t_ray *r, t_cub *game)
{
	return (r->mapy < 0 || r->mapx < 0 || r->mapy >= game->map->height
		|| r->mapx >= game->map->width);
}

static bool	is_wall_tile(char tile)
{
	return (tile == '1' || tile == ' ');
}

static void	advance_ray_in_grid(t_ray *r)
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

static double	compute_perpendicular_distance(t_ray *r)
{
	if (r->side == 0)
		return (r->sidedistx - r->deltadistx);
	return (r->sidedisty - r->deltadisty);
}

static void	calculate_wall_intersection_point(t_ray *r, t_player *p)
{
	if (r->side == 0)
		r->wall_x = p->pos_y + r->wall_distance * r->diry;
	else
		r->wall_x = p->pos_x + r->wall_distance * r->dirx;
	r->wall_x -= floor(r->wall_x);
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
