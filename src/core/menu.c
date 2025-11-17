/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/07 12:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	load_texture_generic(t_cub *data, t_texture **tex_ptr, char *path)
{
	*tex_ptr = malloc(sizeof(t_texture));
	if (!*tex_ptr)
		return (0);
	(*tex_ptr)->img = mlx_xpm_file_to_image(data->mlx, path,
		&(*tex_ptr)->width, &(*tex_ptr)->height);
	if (!(*tex_ptr)->img)
	{
		printf("Warning: Could not load %s\n", path);
		free(*tex_ptr);
		*tex_ptr = NULL;
		return (0);
	}
	(*tex_ptr)->addr = mlx_get_data_addr((*tex_ptr)->img,
		&(*tex_ptr)->bits_per_pixel, &(*tex_ptr)->line_length,
		&(*tex_ptr)->endian);
	return (1);
}

int	load_menu_texture(t_cub *data)
{
	if (!load_texture_generic(data, &data->menu_texture, "textures/menu.xpm"))
	{
		data->menu_texture = malloc(sizeof(t_texture));
		if (!data->menu_texture)
			return (0);
		data->menu_texture->width = 64;
		data->menu_texture->height = 64;
		data->menu_texture->addr = NULL;
		data->menu_texture->bits_per_pixel = 32;
		data->menu_texture->line_length = 256;
		data->menu_texture->endian = 0;
		data->menu_texture->img = NULL;
	}
	data->start_button = malloc(sizeof(t_button));
	if (!data->start_button)
		return (free(data->menu_texture), data->menu_texture = NULL, 0);
	data->start_button->x = 0;
	data->start_button->y = 0;
	data->start_button->width = WIDTH;
	data->start_button->height = HEIGHT;
	return (1);
}

int	is_button_clicked(t_button *button, int mouse_x, int mouse_y)
{
	return (mouse_x >= button->x && mouse_x <= button->x + button->width
		&& mouse_y >= button->y && mouse_y <= button->y + button->height);
}

int	load_win_texture(t_cub *data)
{
	return (load_texture_generic(data, &data->win_texture, "textures/WIN.xpm"));
}

int	load_gameover_texture(t_cub *data)
{
	return (load_texture_generic(data, &data->gameover_texture, "textures/gameover.xpm"));
}
