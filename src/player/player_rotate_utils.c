/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/04 12:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	compute_rotated_x(double x, double y, double angle)
{
	return (x * cos(angle) - y * sin(angle));
}

double	compute_rotated_y(double x, double y, double angle)
{
	return (x * sin(angle) + y * cos(angle));
}

void	apply_rotation_to_direction(t_player *plr, double rotation_angle)
{
	double	temp_x;
	double	temp_y;

	temp_x = plr->dirx;
	temp_y = plr->diry;
	plr->dirx = compute_rotated_x(temp_x, temp_y, rotation_angle);
	plr->diry = compute_rotated_y(temp_x, temp_y, rotation_angle);
}

void	apply_rotation_to_camera_plane(t_player *plr, double rotation_angle)
{
	double	backup_plane_x;
	double	backup_plane_y;

	backup_plane_x = plr->planex;
	backup_plane_y = plr->planey;
	plr->planex = compute_rotated_x(backup_plane_x, backup_plane_y,
			rotation_angle);
	plr->planey = compute_rotated_y(backup_plane_x, backup_plane_y,
			rotation_angle);
}

void	execute_rotation(t_cub *game, double angle)
{
	apply_rotation_to_direction(game->player, angle);
	apply_rotation_to_camera_plane(game->player, angle);
	game->player->yaw += angle;
}
