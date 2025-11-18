/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:43:29 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:47:27 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_wall(char **map, int x, int y, t_cub *data)
{
	if (y < 0 || y >= data->map->height || x < 0)
		return (1);
	if (!map[y] || x >= (int)ft_strlen(map[y]))
		return (1);
	if (map[y][x] == '1')
		return (1);
	if (is_door_character(map[y][x]) && is_door_closed(data, x, y))
		return (1);
	return (0);
}

static void	update_animation(t_mob *m, double dt)
{
	m->t_anim += dt;
	if (m->t_anim > 0.3)
	{
		m->t_anim = 0.0;
		m->frame ^= 1;
	}
}

typedef struct s_mob_move
{
	double	dx;
	double	dy;
	double	dt;
}			t_mob_move;

static void	try_move(t_mob *m, t_cub *data, t_mob_move move)
{
	double	r;
	double	nx;
	double	ny;

	r = 0.20;
	nx = m->x + move.dx * data->mob_speed * move.dt;
	ny = m->y + move.dy * data->mob_speed * move.dt;
	if (!is_wall(data->map->map_tab, (int)(nx + (move.dx > 0 ? r : -r)),
			(int)(m->y), data))
		m->x = nx;
	if (!is_wall(data->map->map_tab, (int)(m->x), (int)(ny + (move.dy > 0 ? r :
					-r)), data))
		m->y = ny;
}

void	mob_update(t_cub *data, double dt)
{
	double		dx;
	double		dy;
	double		len;
	t_mob_move	move;

	if (!data->mob)
		return ;
	update_animation(data->mob, dt);
	dx = data->player->pos_x - data->mob->x;
	dy = data->player->pos_y - data->mob->y;
	len = sqrt(dx * dx + dy * dy);
	if (len < 0.5 && data->game_state == GAME_PLAYING)
	{
		data->game_state = GAME_LOST;
		data->game_end_time = now_ms();
		data->gameover_display_until_ms = now_ms() + 5000;
		return ;
	}
	if (len < 0.5)
		return ;
	dx /= len;
	dy /= len;
	move.dx = dx;
	move.dy = dy;
	move.dt = dt;
	try_move(data->mob, data, move);
}

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

void	mob_render(t_cub *data)
{
	if (!data->mob)
		return ;
	data->sprite->x = data->mob->x;
	data->sprite->y = data->mob->y;
	data->sprite->texture = data->mob->img[data->mob->frame];
	render_sprite(data);
}
