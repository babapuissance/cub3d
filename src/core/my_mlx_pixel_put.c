/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:42:48 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:47:06 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	int		pixels_per_line;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	pixels_per_line = data->line_length / (data->bits_per_pixel / 8);
	if (x >= pixels_per_line)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
