/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:30:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 17:30:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	find_spawn(t_cub *data, double *x, double *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->height)
	{
		j = 0;
		while (data->map->map_tab[i][j])
		{
			if (data->map->map_tab[i][j] == '6')
			{
				*x = j + 0.5;
				*y = i + 0.5;
				data->map->map_tab[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
	*x = data->player->pos_x + 5.0;
	*y = data->player->pos_y + 5.0;
}

void	init_mob(t_cub *data)
{
	data->mob = malloc(sizeof(t_mob));
	if (!data->mob)
		return ;
	find_spawn(data, &data->mob->x, &data->mob->y);
	data->mob_spawn_x = data->mob->x;
	data->mob_spawn_y = data->mob->y;
	data->mob->frame = 0;
	data->mob->t_anim = 0.0;
	data->mob->img[0] = load_texture_from_xpm(data, "textures/monster.xpm");
	data->mob->img[1] = load_texture_from_xpm(data,
			"textures/monstre_work.xpm");
}

int	check_collision(t_cub *data, double len)
{
	if (len < 0.5 && data->game_state == GAME_PLAYING)
	{
		data->game_state = GAME_LOST;
		data->game_end_time = now_ms();
		data->gameover_display_until_ms = now_ms() + 5000;
		return (1);
	}
	if (len < 0.5)
		return (1);
	return (0);
}

void	mob_render(t_cub *data)
{
	if (!data->mob)
		return ;
	data->sprite->x = data->mob->x;
	data->sprite->y = data->mob->y;
	data->sprite->texture = data->mob->img[data->mob->frame];
	render_sprite(data);
}
