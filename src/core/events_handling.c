/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:05:31 by nbariol-          #+#    #+#             */
/*   Updated: 2025/11/18 16:06:09 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_close_window(t_cub *cub)
{
	free_data(cub);
	exit(EXIT_SUCCESS);
}

static void	handle_mouse_toggle(t_cub *cub)
{
	cub->player->capture_mouse = !cub->player->capture_mouse;
	if (cub->player->capture_mouse)
		mlx_mouse_hide(cub->mlx, cub->win);
	else
		mlx_mouse_show(cub->mlx, cub->win);
}

static void	handle_movement_keys(int keysym, t_cub *cub)
{
	if (keysym == XK_w)
		cub->player->moving_y = 1;
	if (keysym == XK_s)
		cub->player->moving_y = -1;
	if (keysym == XK_a)
		cub->player->moving_x = -1;
	if (keysym == XK_d)
		cub->player->moving_x = 1;
	if (keysym == XK_Left)
		cub->player->rotate = -1;
	if (keysym == XK_Right)
		cub->player->rotate = 1;
}

int	key_hook(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		ft_close_window(cub);
	if (cub->game_state == GAME_MENU)
		return (0);
	if (keysym == XK_m)
		handle_mouse_toggle(cub);
	if (keysym == XK_space)
		toggle_door_state(cub);
	handle_movement_keys(keysym, cub);
	return (0);
}

int	key_release_handler(int keysym, t_cub *cub)
{
	if (keysym == XK_w || keysym == XK_s)
		cub->player->moving_y = 0;
	if (keysym == XK_a || keysym == XK_d)
		cub->player->moving_x = 0;
	if (keysym == XK_Left || keysym == XK_Right)
		cub->player->rotate = 0;
	return (0);
}
