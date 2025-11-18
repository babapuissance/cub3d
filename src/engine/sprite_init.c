/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:43:35 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:47:36 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	find_spawn_point(t_cub *data, double *x, double *y, int attempts)
{
	int	map_x;
	int	map_y;

	if (attempts >= MOB_SPAWN_ATTEMPTS)
	{
		*x = data->player->pos_x + 5.0;
		*y = data->player->pos_y + 5.0;
		return (0);
	}
	map_x = (rand() % (data->map->width - 2)) + 1;
	map_y = (rand() % (data->map->height - 2)) + 1;
	if (data->map->map_tab[map_y][map_x] == '0')
	{
		*x = map_x + 0.5;
		*y = map_y + 0.5;
		return (1);
	}
	return (0);
}

static void	find_random_spawn(t_cub *data, double *x, double *y)
{
	int	attempts;

	attempts = 0;
	while (attempts < MOB_SPAWN_ATTEMPTS)
	{
		if (find_spawn_point(data, x, y, attempts))
			return ;
		attempts++;
	}
}

void	init_sprite(t_cub *data)
{
	double	spawn_x;
	double	spawn_y;

	data->sprite_texture = load_texture_from_xpm(data, "textures/monster.xpm");
	data->screamer_texture = load_texture_from_xpm(data,
			"textures/monster_scream_face.xpm");
	if (!data->sprite_texture || !data->screamer_texture)
		return ;
	data->sprite = malloc(sizeof(t_sprite));
	if (!data->sprite)
		return ;
	find_random_spawn(data, &spawn_x, &spawn_y);
	data->sprite->x = spawn_x;
	data->sprite->y = spawn_y;
	data->sprite->texture = data->sprite_texture;
}
