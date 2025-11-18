/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:06:09 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 16:06:09 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
