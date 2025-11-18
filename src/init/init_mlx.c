/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:43:45 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:48:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	malloc_error(void)
{
	perror("There was an issue with memory allocation");
	exit(EXIT_FAILURE);
}

static void	window_error(t_cub *cub)
{
	free(cub->mlx);
	malloc_error();
}

static void	image_error(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	free(cub->mlx);
	free(cub);
	malloc_error();
}

static void	initialize_mlx_connection(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (cub->mlx == NULL)
		malloc_error();
}

static void	create_game_window(t_cub *cub)
{
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (cub->win == NULL)
		window_error(cub);
}

static void	create_game_image(t_cub *cub)
{
	cub->img.data = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (cub->img.data == NULL)
		image_error(cub);
	cub->img.addr = mlx_get_data_addr(cub->img.data, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
}

void	initialize_mlx(t_cub *cub)
{
	floor_color(cub);
	ceiling_color(cub);
	initialize_mlx_connection(cub);
	create_game_window(cub);
	create_game_image(cub);
}
