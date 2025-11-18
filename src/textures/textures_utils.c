/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:52 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:49:29 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_texture	*allocate_texture_structure(void)
{
	return (malloc(sizeof(t_texture)));
}

t_texture	*load_texture_from_xpm(t_cub *data, const char *path)
{
	t_texture	*tex;

	tex = allocate_texture_structure();
	if (!tex)
		return (NULL);
	tex->img = mlx_xpm_file_to_image(data->mlx, (char *)path, &tex->width,
			&tex->height);
	if (!tex->img)
		return (free(tex), NULL);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	return (tex);
}
