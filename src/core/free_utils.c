/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:05:31 by nbariol-          #+#    #+#             */
/*   Updated: 2025/11/18 13:42:17 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_free(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_map_data(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->infos)
	{
		i = 0;
		while (map->infos[i])
		{
			free(map->infos[i]);
			i++;
		}
		free(map->infos);
	}
	if (map->map != NULL)
	{
		free(map->map);
	}
	if (map->map_tab)
	{
		ft_free(map->map_tab);
	}
	free(map);
}

void	free_texture_strings(t_cub *data)
{
	if (data->no_texture)
		free(data->no_texture);
	if (data->so_texture)
		free(data->so_texture);
	if (data->ea_texture)
		free(data->ea_texture);
	if (data->we_texture)
		free(data->we_texture);
}
