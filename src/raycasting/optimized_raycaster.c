/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/02 12:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	render_ceiling_optimized(t_cub *game, int col, int limit)
{
	int	row;
	int	sky_color;

	sky_color = (game->ceiling_rgb->r << 16) | (game->ceiling_rgb->g << 8) | game->ceiling_rgb->b;
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

	ground_color = (game->floor_rgb->r << 16) | (game->floor_rgb->g << 8) | game->floor_rgb->b;
	row = start;
	while (row < HEIGHT)
	{
		optimized_pixel_put(&game->img, col, row, ground_color);
		row++;
	}
}

static void	render_wall_optimized(t_cub *game, int col, t_texture *tex, int tex_x)
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

int	raycasting(t_cub *data)
{
	int	screen_column;
	t_texture	*wall_tex;
	int			texture_x_coord;

	screen_column = 0;
	while (screen_column < WIDTH)
	{
		cast_single_ray(data, screen_column);
		wall_tex = select_texture(data, data->ray);
		calculate_texture_coordinates(data->ray, wall_tex, &texture_x_coord);
		draw_column(data, screen_column, wall_tex, texture_x_coord);
		screen_column++;
	}
	return (0);
}
