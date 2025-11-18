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

static double	get_offset(double dir_value)
{
	if (dir_value <= 0)
		return (-0.20);
	return (0.20);
}

static void	try_move(t_mob *m, t_cub *data, t_mob_move move)
{
	double	nx;
	double	ny;

	nx = m->x + move.dx * data->mob_speed * move.dt;
	ny = m->y + move.dy * data->mob_speed * move.dt;
	if (!is_wall(data->map->map_tab, (int)(nx + get_offset(move.dx)),
		(int)(m->y), data))
		m->x = nx;
	if (!is_wall(data->map->map_tab, (int)(m->x),
		(int)(ny + get_offset(move.dy)), data))
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
	if (check_collision(data, len))
		return ;
	dx /= len;
	dy /= len;
	move.dx = dx;
	move.dy = dy;
	move.dt = dt;
	try_move(data->mob, data, move);
}
