/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_render_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:10:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 17:10:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	clamp_texture_x(double u, t_texture *tex)
{
	int	tex_x;

	tex_x = (int)(u * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

int	calc_door_tex_y(t_cub *g, int y, int line_h)
{
	double	step;
	double	tex_pos;
	int		tex_y;

	step = (double)g->door_texture->height / line_h;
	tex_pos = (y - g->w_height / 2 + line_h / 2) * step;
	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= g->door_texture->height)
		tex_y = g->door_texture->height - 1;
	return (tex_y);
}

int	compute_texture_y(t_cub *g, t_texture *tex, int y_pos, int line_h)
{
	int	offset;

	offset = y_pos * 256 - g->w_height * 128 + line_h * 128;
	return (((offset * tex->height) / line_h) / 256);
}

void	render_closed_doors(t_cub *g)
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
