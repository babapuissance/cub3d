/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:43:25 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:47:24 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	process_rotation_input(t_cub *game)
{
	if (game->player->rotate == 1)
		execute_rotation(game, game->rotationspeed);
	else if (game->player->rotate == -1)
		execute_rotation(game, -game->rotationspeed);
}

static void	handle_player_actions(t_cub *game)
{
	move_player(game);
	process_rotation_input(game);
	mob_update(game, 0.016);
}

static void	render_game_frame(t_cub *g)
{
	raycasting(g);
	render_doors(g);
	mob_render(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.data, 0, 0);
	render_minimap(g);
}

static int	handle_game_state_display(t_cub *game)
{
	if (game->game_state == GAME_MENU && game->menu_texture
		&& game->menu_texture->img)
		mlx_put_image_to_window(game->mlx, game->win,
			game->menu_texture->img, 0, 0);
	else if (game->game_state == GAME_WON && game->win_texture
		&& game->win_texture->img)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->win_texture->img, 0, 0);
		if (now_ms() >= game->win_display_until_ms)
			game->game_state = GAME_MENU;
	}
	else if (game->game_state == GAME_LOST && game->gameover_texture
		&& game->gameover_texture->img)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->gameover_texture->img, 0, 0);
		if (now_ms() >= game->gameover_display_until_ms)
			game->game_state = GAME_MENU;
	}
	else
		return (1);
	return (0);
}

int	render_frame(t_cub *game)
{
	static size_t	tick_count = 0;

	if (!handle_game_state_display(game))
		return (0);
	if (tick_count > TICK_SPEED)
	{
		handle_player_actions(game);
		render_game_frame(game);
		if (game->game_state == GAME_PLAYING)
		{
			if (check_all_doors_open(game))
				trigger_victory(game);
		}
		tick_count = 0;
	}
	tick_count++;
	return (0);
}
