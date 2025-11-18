/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:42 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:49:24 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_texture_path(t_cub *game, char *id, char **dest, char *err)
{
	char	**config_lines;
	char	**parsed_tokens;
	int		line_idx;

	config_lines = game->map->infos;
	line_idx = 0;
	while (config_lines[line_idx] && !ft_strnstr(config_lines[line_idx], id,
			ft_strlen(config_lines[line_idx])))
		line_idx++;
	if (!config_lines[line_idx])
		return (printf("%s", err), 0);
	parsed_tokens = split_on_space_tab(config_lines[line_idx]);
	if (ft_strlen(config_lines[line_idx]) <= 4)
	{
		ft_free(parsed_tokens);
		return (printf("%s", err), 0);
	}
	*dest = ft_strtrim(parsed_tokens[1], "\n");
	ft_free(parsed_tokens);
	if (!is_correct_extension(*dest, "xpm"))
		return (printf("Invalid %s texture extension.\n", id), 0);
	return (1);
}

static int	load_wall_texture(t_cub *d, char *id, char **path_ptr,
		t_texture **tex_ptr)
{
	if (!parse_texture_path(d, id, path_ptr, "Texture reading failed.\n"))
		return (0);
	*tex_ptr = load_texture_from_xpm(d, *path_ptr);
	if (!*tex_ptr)
		return (0);
	if ((*tex_ptr)->height > 2048 || (*tex_ptr)->width > 2048)
		return (0);
	return (1);
}

int	north_texture(t_cub *data)
{
	return (load_wall_texture(data, "NO", &data->no_texture,
			&data->no_texture_img));
}

int	south_texture(t_cub *data)
{
	return (load_wall_texture(data, "SO", &data->so_texture,
			&data->so_texture_img));
}

int	east_texture(t_cub *data)
{
	return (load_wall_texture(data, "EA", &data->ea_texture,
			&data->ea_texture_img));
}

int	west_texture(t_cub *data)
{
	return (load_wall_texture(data, "WE", &data->we_texture,
			&data->we_texture_img));
}
