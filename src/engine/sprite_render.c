/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:43:39 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:47:30 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	calculate_sprite_transform(t_cub *d, double *tr_x, double *tr_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = d->sprite->x - d->player->pos_x;
	sprite_y = d->sprite->y - d->player->pos_y;
	inv_det = 1.0 / (d->player->planex * d->player->diry - d->player->dirx
			* d->player->planey);
	*tr_x = inv_det * (d->player->diry * sprite_x - d->player->dirx * sprite_y);
	*tr_y = inv_det * (-d->player->planey * sprite_x + d->player->planex
			* sprite_y);
}

static void	set_sprite_screen_pos(double tr_x, double tr_y, int *screen_x,
		int *sprite_h)
{
	*screen_x = (int)((WIDTH / 2) * (1 + tr_x / tr_y));
	*sprite_h = abs((int)(HEIGHT / tr_y));
}

static void	draw_sprite_pixel(t_cub *d, int x, int y, int prm[5])
{
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = (int)((x - prm[2]) * d->sprite->texture->width / prm[4]);
	tex_y = (int)((y - prm[0]) * (double)d->sprite->texture->height / prm[1]);
	if (tex_x < 0 || tex_x >= d->sprite->texture->width)
		return ;
	if (tex_y < 0 || tex_y >= d->sprite->texture->height)
		return ;
	color = get_texture_color(d->sprite->texture, tex_x, tex_y);
	if ((color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(&d->img, x, y, color);
}

static void	draw_sprite_column(t_cub *d, int x, int prm[5], double tr_y)
{
	int	y;

	if (x < 0 || x >= WIDTH || tr_y <= 0)
		return ;
	if (tr_y >= d->z_buffer[x])
		return ;
	y = prm[0];
	while (y < prm[3] && y < HEIGHT)
	{
		if (y >= 0)
			draw_sprite_pixel(d, x, y, prm);
		y++;
	}
}

void	render_sprite(t_cub *data)
{
	double	transform_x;
	double	transform_y;
	int		sprite_height;
	int		sprite_width;
	int		draw_start;
	int		draw_end;
	int		sprite_left;
	int		sprite_params[5];
	int		x;

	if (!data->sprite || !data->sprite->texture)
		return ;
	calculate_sprite_transform(data, &transform_x, &transform_y);
	if (transform_y <= 0)
		return ;
	set_sprite_screen_pos(transform_x, transform_y, &sprite_left,
		&sprite_height);
	sprite_width = sprite_height * data->sprite->texture->width
		/ data->sprite->texture->height;
	draw_end = HEIGHT / 2 + sprite_height / 2;
	draw_start = HEIGHT / 2 - sprite_height / 2;
	sprite_left = sprite_left - sprite_width / 2;
	sprite_params[0] = draw_start;
	sprite_params[1] = sprite_height;
	sprite_params[2] = sprite_left;
	sprite_params[3] = draw_end;
	sprite_params[4] = sprite_width;
	x = sprite_left;
	while (x < sprite_left + sprite_width && x < WIDTH)
	{
		if (x >= 0)
			draw_sprite_column(data, x, sprite_params, transform_y);
		x++;
	}
}
