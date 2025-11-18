/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_optional.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:46 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:49:27 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	load_optional_texture(t_cub *d, char *id, char **path,
		t_texture **tex_ptr)
{
	if (!parse_texture_path(d, id, path, "Texture reading failed.\n"))
		return (0);
	*tex_ptr = load_texture_from_xpm(d, *path);
	if (!*tex_ptr)
		return (0);
	if ((*tex_ptr)->height > 2048 || (*tex_ptr)->width > 2048)
		return (0);
	return (1);
}

int	floor_texture(t_cub *data)
{
	char	**config_lines;
	int		line_idx;

	config_lines = data->map->infos;
	line_idx = 0;
	while (config_lines[line_idx] && !ft_strnstr(config_lines[line_idx], "FT",
			ft_strlen(config_lines[line_idx])))
		line_idx++;
	if (!config_lines[line_idx])
	{
		data->floor_texture = NULL;
		return (1);
	}
	return (load_optional_texture(data, "FT", &data->floor_texture,
			&data->floor_texture_img));
}

int	ceiling_texture(t_cub *data)
{
	char	**config_lines;
	int		line_idx;

	config_lines = data->map->infos;
	line_idx = 0;
	while (config_lines[line_idx] && !ft_strnstr(config_lines[line_idx], "CT",
			ft_strlen(config_lines[line_idx])))
		line_idx++;
	if (!config_lines[line_idx])
	{
		data->ceiling_texture = NULL;
		return (1);
	}
	return (load_optional_texture(data, "CT", &data->ceiling_texture,
			&data->ceiling_texture_img));
}
