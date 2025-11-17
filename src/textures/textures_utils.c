/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/05 12:00:00 by nbariol-         ###   ########.fr       */
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
	tex->img = mlx_xpm_file_to_image(data->mlx, (char *)path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (free(tex), NULL);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	return (tex);
}
