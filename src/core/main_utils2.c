/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:42:28 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:42:34 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_data(t_cub *data)
{
	if (!data)
		return ;
	if (data->map)
		free_map_data(data->map);
	if (data->floor_rgb)
		free(data->floor_rgb);
	if (data->ceiling_rgb)
		free(data->ceiling_rgb);
	if (data->player)
		free(data->player);
	if (data->ray)
		free(data->ray);
	if (data->camera_x_cache)
		free(data->camera_x_cache);
	if (data->z_buffer)
		free(data->z_buffer);
	if (data->sprite)
		free(data->sprite);
	free_texture_strings(data);
	free_texture_images(data);
	free_mlx_resources(data);
	free(data);
}

int	read_file_infos(t_cub *data, int fd)
{
	char	*line;
	size_t	i;

	i = 0;
	line = get_next_line(fd);
	while (line && !is_first_or_last_line_valid(line) && i < 100000)
	{
		data->map->infos[i++] = line;
		line = get_next_line(fd);
	}
	data->map->map = line;
	data->map->infos[i] = NULL;
	return (0);
}
