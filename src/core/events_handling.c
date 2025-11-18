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

int	key_hook(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		ft_close_window(cub);
	if (cub->game_state == GAME_MENU)
		return (0);
	if (keysym == XK_m)
	{
		cub->player->capture_mouse = !cub->player->capture_mouse;
		if (cub->player->capture_mouse)
			mlx_mouse_hide(cub->mlx, cub->win);
		else
			mlx_mouse_show(cub->mlx, cub->win);
	}
	if (keysym == XK_space)
		toggle_door_state(cub);
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

static int	move_mouse_event(int pos_h, int pos_v, t_cub *cub)
{
	static int	last_pos_h;
	static int	initialized;
	int			delta;

	(void)pos_v;
	if (!cub->player->capture_mouse)
	{
		initialized = 0;
		return (0);
	}
	if (!initialized)
	{
		last_pos_h = pos_h;
		initialized = 1;
		return (0);
	}
	if (pos_h == WIDTH / 2)
		return (last_pos_h = pos_h, 0);
	delta = last_pos_h - pos_h;
	if (delta != 0)
		execute_rotation(cub, delta * -1 * MOUSE_SPEED * ANGLE_SPEED);
	last_pos_h = pos_h;
	return (0);
}

static int	click_mouse_event(int keycode, int h, int v, t_cub *cub)
{
	if (cub->game_state == GAME_MENU && keycode == KEY_MOUSE_LEFT)
	{
		if (is_button_clicked(cub->start_button, h, v))
		{
			reset_game(cub);
		}
		return (0);
	}
	if (keycode && !cub->player->capture_mouse)
	{
		cub->player->capture_mouse = 1;
		mlx_mouse_hide(cub->mlx, cub->win);
	}
	return (0);
}

void	events_handling(t_cub *cub)
{
	mlx_hook(cub->win, 02, (1L << 0), key_hook, cub);
	mlx_hook(cub->win, 17, (1L << 17), ft_close_window, cub);
	mlx_hook(cub->win, 03, (1L << 1), key_release_handler, cub);
	mlx_hook(cub->win, 6, (1L << 6), move_mouse_event, cub);
	mlx_mouse_hook(cub->win, click_mouse_event, cub);
	mlx_loop_hook(cub->mlx, render_frame, cub);
}
