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
