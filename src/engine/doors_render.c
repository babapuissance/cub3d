/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:43:20 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:47:22 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

typedef struct s_door_proj
{
	double	t;
	double	u;
	int		mode;
}			t_door_proj;

static int	clamp_texture_x(double u, t_texture *tex)
{
	int	tex_x;

	tex_x = (int)(u * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

static int	compute_texture_y(t_cub *g, t_texture *tex, int y_pos, int line_h)
{
	int	offset;

	offset = y_pos * 256 - g->w_height * 128 + line_h * 128;
	return (((offset * tex->height) / line_h) / 256);
}

static void	draw_door_pixel(t_cub *g, int x, int y, t_door_proj proj)
{
	int	tex_x;
	int	tex_y;
	int	color;
	int	line_h;

	line_h = (int)(g->w_height / proj.t);
	tex_x = clamp_texture_x(proj.u, g->door_texture);
	tex_y = compute_texture_y(g, g->door_texture, y, line_h);
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

static int	compute_ray_intersection(t_cub *g, t_door *door, double camera_x,
		double *out_t, double *out_u)
{
	double	rx;
	double	ry;
	double	t;
	double	u;

	rx = g->player->dirx + g->player->planex * camera_x;
	ry = g->player->diry + g->player->planey * camera_x;
	if (door->orient == DOOR_Y)
	{
		if (fabs(rx) < FLOAT_EPSILON)
			return (0);
		t = (door->i - g->player->pos_x) / rx;
		if (t <= 0)
			return (0);
		u = g->player->pos_y + t * ry - door->j;
	}
	else
	{
		if (fabs(ry) < FLOAT_EPSILON)
			return (0);
		t = (door->j - g->player->pos_y) / ry;
		if (t <= 0)
			return (0);
		u = g->player->pos_x + t * rx - door->i;
	}
	if (u < 0.0 || u > 1.0)
		return (0);
	*out_t = t;
	*out_u = u;
	return (1);
}

static void	render_one_door_loop(t_cub *g, t_door *door, int mode)
{
	double		t;
	double		u;
	double		camera_x;
	int			x;
	t_door_proj	proj;

	x = 0;
	while (x < g->w_width)
	{
		camera_x = 2.0 * x / (double)g->w_width - 1.0;
		if (compute_ray_intersection(g, door, camera_x, &t, &u))
		{
			if (!(t >= g->z_buffer[x] && (door->is_closed || mode == 1
						|| mode == 3)))
			{
				proj.t = t;
				proj.u = u;
				proj.mode = mode;
				draw_door_column(g, x, proj);
			}
		}
		x++;
	}
}

static void	render_one_door(t_cub *g, t_door *door)
{
	if (!g->door_texture || !g->door_texture->addr)
		return ;
	render_one_door_loop(g, door, 0);
}

static void	render_closed_doors(t_cub *g)
{
	int	i;

	if (!g->doors || g->door_count == 0)
		return ;
	i = 0;
	while (i < g->door_count)
	{
		if (g->doors[i].is_closed)
			render_one_door(g, &g->doors[i]);
		i++;
	}
}

void	render_doors(t_cub *g)
{
	if (!g->doors || g->door_count == 0)
		return ;
	render_closed_doors(g);
}
