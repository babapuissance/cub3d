/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_raycaster.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:24 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/20 20:20:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	render_ceiling_optimized(t_cub *game, int col, int limit)
{
	int	row;
	int	sky_color;

	sky_color = (game->ceiling_rgb->r << 16) | (game->ceiling_rgb->g << 8)
		| game->ceiling_rgb->b;
	row = 0;
	while (row < limit)
	{
		optimized_pixel_put(&game->img, col, row, sky_color);
		row++;
	}
}

static void	render_floor_optimized(t_cub *game, int col, int start)
{
	int	row;
	int	ground_color;

	ground_color = (game->floor_rgb->r << 16) | (game->floor_rgb->g << 8)
		| game->floor_rgb->b;
	row = start;
	while (row < HEIGHT)
	{
		optimized_pixel_put(&game->img, col, row, ground_color);
		row++;
	}
}

static void	render_wall_optimized(t_cub *game, int col, t_texture *tex,
		int tex_x)
{
	int		y_coord;
	int		texture_y;
	int		pixel_color;
	double	tex_pos;
	double	step;

	step = (double)tex->height / game->ray->line_height;
	tex_pos = (game->ray->draw_start - game->w_height / 2
			+ game->ray->line_height / 2) * step;
	y_coord = game->ray->draw_start;
	while (y_coord <= game->ray->draw_end)
	{
		texture_y = (int)tex_pos;
		pixel_color = get_texture_color(tex, tex_x, texture_y);
		optimized_pixel_put(&game->img, col, y_coord, pixel_color);
		tex_pos += step;
		y_coord++;
	}
}

void	draw_column(t_cub *data, int x, t_texture *texture, int tex_x)
{
	if (data->ceiling_texture_img)
		render_ceiling_textured(data, x, data->ray->draw_start);
	else
		render_ceiling_optimized(data, x, data->ray->draw_start);
	render_wall_optimized(data, x, texture, tex_x);
	if (data->floor_texture_img)
		render_floor_textured(data, x, data->ray->draw_end + 1);
	else
		render_floor_optimized(data, x, data->ray->draw_end + 1);
}

void	cast_single_ray(t_cub *data, int x)
{
	raycast_init(x, data->player, data->ray, data->camera_x_cache[x]);
	dda_init(data->ray, data->player);
	exec_dda(data, data->ray, 0);
	line_height(data->ray, data->player, data);
	data->z_buffer[x] = data->ray->wall_distance;
}
