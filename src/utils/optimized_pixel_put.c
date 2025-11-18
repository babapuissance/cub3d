/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_pixel_put.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:56 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:49:33 by sle-bail         ###   ########.fr       */
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
