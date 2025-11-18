/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:44:04 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:48:11 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	fill_tile_block(t_minimap *m, int x, int y, int color)
{
	int	row;
	int	col;

	row = 0;
	while (row < m->tile_size)
	{
		col = 0;
		while (col < m->tile_size)
		{
			set_image_pixel(m->img, x + col, y + row, color);
			col++;
		}
		row++;
	}
}

static int	get_tile_color(char tile_type)
{
	if (tile_type == 'P')
		return (MMAP_COLOR_PLAYER);
	else if (tile_type == '1')
		return (MMAP_COLOR_WALL);
	else if (tile_type == '0')
		return (MMAP_COLOR_FLOOR);
	else
		return (MMAP_COLOR_SPACE);
}

static void	paint_single_tile(t_minimap *m, int grid_x, int grid_y)
{
	int	pixel_x;
	int	pixel_y;
	int	color;

	pixel_x = grid_x * m->tile_size;
	pixel_y = grid_y * m->tile_size;
	color = get_tile_color(m->map[grid_y][grid_x]);
	fill_tile_block(m, pixel_x, pixel_y, color);
}

static void	paint_minimap_tiles(t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->size)
	{
		x = 0;
		while (x < minimap->size)
		{
			if (minimap->map[y] && minimap->map[y][x])
				paint_single_tile(minimap, x, y);
			x++;
		}
		y++;
	}
}

void	render_minimap_image(t_cub *data, t_minimap *minimap)
{
	int	img_size;

	img_size = MMAP_PIXEL_SIZE + minimap->tile_size;
	init_img(data, &data->minimap, img_size, img_size);
	paint_minimap_tiles(minimap);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.data,
		minimap->tile_size, data->w_height - (MMAP_PIXEL_SIZE
			+ (minimap->tile_size * 2)));
	if (data->minimap.data)
		mlx_destroy_image(data->mlx, data->minimap.data);
}
