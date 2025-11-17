/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 09:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/06 10:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	allocate_door_state_row(t_cub *data, int y)
{
	int	x;

	data->door_state[y] = malloc(sizeof(char) * (data->map->width + 1));
	if (!data->door_state[y])
		return (0);
	x = 0;
	while (x < data->map->width)
		data->door_state[y][x++] = '0';
	data->door_state[y][x] = '\0';
	return (1);
}

int	init_door_state(t_cub *data)
{
	int	y;

	data->door_state = malloc(sizeof(char *) * data->map->height);
	if (!data->door_state)
		return (0);
	y = 0;
	while (y < data->map->height)
	{
		if (!allocate_door_state_row(data, y))
		{
			free_door_state(data->door_state, y);
			return (0);
		}
		y++;
	}
	return (1);
}

void	free_door_state(char **door_state, int height)
{
	int	y;

	if (!door_state)
		return ;
	y = 0;
	while (y < height)
	{
		free(door_state[y]);
		y++;
	}
	free(door_state);
}

int	door_texture_loader(t_cub *data)
{
	data->door_texture = malloc(sizeof(t_texture));
	if (!data->door_texture)
		return (0);
	data->door_texture->img = mlx_xpm_file_to_image(data->mlx,
		"textures/porte.xpm", &data->door_texture->width,
		&data->door_texture->height);
	if (!data->door_texture->img)
	{
		free(data->door_texture);
		data->door_texture = NULL;
		return (0);
	}
	data->door_texture->addr = mlx_get_data_addr(data->door_texture->img,
		&data->door_texture->bits_per_pixel,
		&data->door_texture->line_length,
		&data->door_texture->endian);
	if (!data->door_texture->addr)
	{
		mlx_destroy_image(data->mlx, data->door_texture->img);
		free(data->door_texture);
		data->door_texture = NULL;
		return (0);
	}
	return (1);
}
