/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/01 10:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_texture_pointers(t_cub *data)
{
	data->no_texture = NULL;
	data->so_texture = NULL;
	data->ea_texture = NULL;
	data->we_texture = NULL;
	data->no_texture_img = NULL;
	data->so_texture_img = NULL;
	data->ea_texture_img = NULL;
	data->we_texture_img = NULL;
	data->door_texture = NULL;
}

void	init_window_dimensions(t_cub *data)
{
	data->w_height = HEIGHT;
	data->w_width = WIDTH;
}

int	init_map_structure(t_cub *data)
{
	int	i;

	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (0);
	data->map->infos = malloc(sizeof(char *) * 101);
	if (!data->map->infos)
	{
		free(data->map);
		data->map = NULL;
		return (0);
	}
	i = 0;
	while (i < 101)
	{
		data->map->infos[i] = NULL;
		i++;
	}
	data->map->map = NULL;
	data->map->map_tab = NULL;
	data->map->height = 0;
	data->map->width = 0;
	return (1);
}

int	init_game_objects(t_cub *data)
{
	data->floor_rgb = malloc(sizeof(t_rgb));
	if (!data->floor_rgb)
		return (0);
	data->ceiling_rgb = malloc(sizeof(t_rgb));
	if (!data->ceiling_rgb)
		return (free(data->floor_rgb), (0));
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (free(data->floor_rgb), free(data->ceiling_rgb), (0));
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		return (free(data->floor_rgb), free(data->ceiling_rgb),
			free(data->player), (0));
	return (1);
}

void	init_mlx_pointers(t_cub *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->img.data = NULL;
	data->img.addr = NULL;
}
