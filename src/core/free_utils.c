/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/07 16:00:00 by nbariol-         ###   ########.fr       */
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

void	free_texture_image(void *mlx, t_texture *texture_img)
{
	if (!texture_img)
		return ;
	if (texture_img->img)
		mlx_destroy_image(mlx, texture_img->img);
	free(texture_img);
}

void	free_texture_images(t_cub *data)
{
	free_texture_image(data->mlx, data->no_texture_img);
	free_texture_image(data->mlx, data->so_texture_img);
	free_texture_image(data->mlx, data->ea_texture_img);
	free_texture_image(data->mlx, data->we_texture_img);
	free_texture_image(data->mlx, data->sprite_texture);
	free_texture_image(data->mlx, data->door_texture);
	free_texture_image(data->mlx, data->menu_texture);
	free_texture_image(data->mlx, data->win_texture);
	free_texture_image(data->mlx, data->gameover_texture);
	if (data->start_button)
		free(data->start_button);
	if (data->door_state)
		free_door_state(data->door_state, data->map->height);
	if (data->doors)
		free(data->doors);
}

void	free_mlx_resources(t_cub *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->img.data)
		mlx_destroy_image(data->mlx, data->img.data);
	if (data->mlx)
		free(data->mlx);
}
