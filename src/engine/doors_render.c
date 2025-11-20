/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:43:20 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 17:20:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

typedef struct s_door_proj
{
	double	t;
	double	u;
	int		mode;
}			t_door_proj;

static void	draw_door_pixel(t_cub *g, int x, int y, t_door_proj proj)
{
	int		tex_x;
	int		tex_y;
	int		color;
	int		line_h;

	line_h = (int)(g->w_height / proj.t);
	tex_x = clamp_texture_x(proj.u, g->door_texture);
	tex_y = calc_door_tex_y(g, y, line_h);
	color = get_texture_color(g->door_texture, tex_x, tex_y);
	if ((color & 0x00FFFFFF) != 0 && (proj.mode == 0 || proj.mode == 3
			|| proj.mode == 1))
		my_mlx_pixel_put(&g->img, x, y, color);
}

static void	draw_door_column(t_cub *g, int x, t_door_proj proj)
{
	int	line_h;
	int	draw_start;
	int	draw_end;
	int	y;

	line_h = (int)(g->w_height / proj.t);
	draw_start = -line_h / 2 + g->w_height / 2;
	draw_end = line_h / 2 + g->w_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= g->w_height)
		draw_end = g->w_height - 1;
	if (draw_start > draw_end)
		return ;
	y = draw_start;
	while (y <= draw_end)
	{
		draw_door_pixel(g, x, y, proj);
		y++;
	}
	if ((proj.mode == 0 || proj.mode == 1) && proj.t < g->z_buffer[x])
		g->z_buffer[x] = proj.t;
}

static void	render_one_door_loop(t_cub *g, t_door *door, int mode)
{
	t_ray_result	result;
	double			camera_x;
	int				x;
	t_door_proj		proj;

	x = 0;
	while (x < g->w_width)
	{
		camera_x = 2.0 * x / (double)g->w_width - 1.0;
		result = compute_ray_intersection(g, door, camera_x);
		if (result.hit)
		{
			if (!(result.t >= g->z_buffer[x] && (door->is_closed || mode == 1
						|| mode == 3)))
			{
				proj.t = result.t;
				proj.u = result.u;
				proj.mode = mode;
				draw_door_column(g, x, proj);
			}
		}
		x++;
	}
}

void	render_one_door(t_cub *g, t_door *door)
{
	if (!g->door_texture || !g->door_texture->addr)
		return ;
	render_one_door_loop(g, door, 0);
}

void	render_doors(t_cub *g)
{
	if (!g->doors || g->door_count == 0)
		return ;
	render_closed_doors(g);
}
