/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:44:08 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:48:14 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	calculate_map_offset(t_minimap *m, int total_size, int pos)
{
	if (pos > m->view_dist && total_size - pos > m->view_dist + 1)
		return (pos - m->view_dist);
	if (pos > m->view_dist && total_size - pos <= m->view_dist + 1)
		return (total_size - m->size);
	return (0);
}

static char	get_cell_type(t_cub *d, t_minimap *m, int x, int y)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = x + m->offset_x;
	map_y = y + m->offset_y;
	if (map_y >= d->map->height || map_x >= d->map->width)
		return ('\0');
	if ((int)d->player->pos_x == map_x && (int)d->player->pos_y == map_y)
		return ('P');
	cell = d->map->map_tab[map_y][map_x];
	if (cell == '1')
		return ('1');
	if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W'
		|| cell == 'D')
		return ('0');
	return ('\0');
}

static char	*create_minimap_row(t_cub *data, t_minimap *minimap, int y)
{
	char	*row;
	int		x;

	row = ft_calloc(minimap->size + 1, sizeof(*row));
	if (!row)
		return (NULL);
	x = 0;
	while (x < minimap->size)
	{
		row[x] = get_cell_type(data, minimap, x, y);
		x++;
	}
	return (row);
}

static char	**build_minimap_grid(t_cub *data, t_minimap *minimap)
{
	char	**grid;
	int		y;

	grid = ft_calloc(minimap->size + 1, sizeof(*grid));
	if (!grid)
		return (NULL);
	y = 0;
	while (y < minimap->size)
	{
		grid[y] = create_minimap_row(data, minimap, y);
		if (!grid[y])
		{
			free_tab((void **)grid);
			return (NULL);
		}
		y++;
	}
	return (grid);
}

void	render_minimap(t_cub *data)
{
	t_minimap	minimap;

	minimap.map = NULL;
	minimap.img = &data->minimap;
	minimap.view_dist = MMAP_VIEW_DIST;
	minimap.size = (2 * minimap.view_dist) + 1;
	minimap.tile_size = MMAP_PIXEL_SIZE / (2 * minimap.view_dist);
	minimap.offset_x = calculate_map_offset(&minimap, data->map->width,
			(int)data->player->pos_x);
	minimap.offset_y = calculate_map_offset(&minimap, data->map->height,
			(int)data->player->pos_y);
	minimap.rotation = get_minimap_rotation_from_spawn(
			data->player->player_dir);
	minimap.map = build_minimap_grid(data, &minimap);
	if (!minimap.map)
	{
		err_msg(NULL, "Error\nMalloc failed for minimap", 0);
		return ;
	}
	if (MMAP_DEBUG_MSG)
		debug_display_minimap(&minimap);
	render_minimap_image(data, &minimap);
	free_tab((void **)minimap.map);
}
