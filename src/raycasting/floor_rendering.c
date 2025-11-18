/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:19 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:49:10 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

typedef struct s_ray_direction
{
	double				x;
	double				y;
}						t_ray_direction;

static t_ray_direction	get_floor_ray_direction(t_cub *game, int x)
{
	t_ray_direction	ray_dir;
	double			camera_x;

	camera_x = game->camera_x_cache[x];
	ray_dir.x = game->player->dirx + game->player->planex * camera_x;
	ray_dir.y = game->player->diry + game->player->planey * camera_x;
	return (ray_dir);
}

static void	calculate_floor_position(t_cub *game, int y, t_ray_direction ray,
		double *out)
{
	double	row_distance;
	double	pos_z;

	pos_z = 0.5 * HEIGHT;
	row_distance = pos_z / (y - HEIGHT / 2.0);
	out[0] = game->player->pos_x + row_distance * ray.x;
	out[1] = game->player->pos_y + row_distance * ray.y;
}

static int	get_tiled_texture_color(t_texture *tex, double x, double y)
{
	int	tex_x;
	int	tex_y;
	int	size;

	x = fmod(x, 1.0);
	y = fmod(y, 1.0);
	if (x < 0)
		x += 1.0;
	if (y < 0)
		y += 1.0;
	size = tex->width;
	if (tex->height < size)
		size = tex->height;
	tex_x = (int)(x * (size - 1)) % size;
	tex_y = (int)(y * (size - 1)) % size;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	return (get_texture_color(tex, tex_x, tex_y));
}

static int	get_floor_texture_color(t_cub *game, double floor_x, double floor_y)
{
	return (get_tiled_texture_color(game->floor_texture_img, floor_x, floor_y));
}

static int	get_ceiling_texture_color(t_cub *game, double ceil_x, double ceil_y)
{
	return (get_tiled_texture_color(game->ceiling_texture_img, ceil_x, ceil_y));
}

void	render_floor_textured(t_cub *game, int x, int start_y)
{
	int				y;
	t_ray_direction	ray;
	double			floor_pos[2];
	int				color;

	ray = get_floor_ray_direction(game, x);
	y = start_y;
	while (y < HEIGHT)
	{
		calculate_floor_position(game, y, ray, floor_pos);
		color = get_floor_texture_color(game, floor_pos[0], floor_pos[1]);
		optimized_pixel_put(&game->img, x, y, color);
		y++;
	}
}

void	render_ceiling_textured(t_cub *game, int x, int end_y)
{
	int				y;
	t_ray_direction	ray;
	double			ceiling_pos[2];
	int				color;

	ray = get_floor_ray_direction(game, x);
	y = 0;
	while (y < end_y)
	{
		calculate_floor_position(game, HEIGHT - y, ray, ceiling_pos);
		color = get_ceiling_texture_color(game, ceiling_pos[0], ceiling_pos[1]);
		optimized_pixel_put(&game->img, x, y, color);
		y++;
	}
}
