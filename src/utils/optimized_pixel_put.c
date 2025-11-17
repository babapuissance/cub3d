/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/09 10:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_position_valid(int x, int y)
{
	return (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT);
}

static int	calculate_pixel_offset(t_img *img, int x, int y)
{
	return (y * (img->line_length / 4) + x);
}

static void	set_pixel_color_direct(t_img *img, int offset, int color)
{
	((int *)img->addr)[offset] = color;
}

int	optimized_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	if (!is_position_valid(x, y))
		return (1);
	offset = calculate_pixel_offset(img, x, y);
	set_pixel_color_direct(img, offset, color);
	return (0);
}
