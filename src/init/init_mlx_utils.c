/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:10:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 18:10:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	malloc_error(void)
{
	perror("There was an issue with memory allocation");
	exit(EXIT_FAILURE);
}

void	window_error(t_cub *cub)
{
	free(cub->mlx);
	malloc_error();
}

void	image_error(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	free(cub->mlx);
	free(cub);
	malloc_error();
}
