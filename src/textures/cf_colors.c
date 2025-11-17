/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cf_colors.c                                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/05 14:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define RGB_MIN 0
#define RGB_MAX 255
#define RGB_COMPONENTS 3

static int	skip_whitespace_and_get_next(char *str, int *idx)
{
	while (str[*idx] && (str[*idx] == ' ' || str[*idx] == '\t'))
		(*idx)++;
	return (str[*idx]);
}

static int	extract_single_rgb_value(char *line, int *position)
{
	int	value;
	int	started;

	skip_whitespace_and_get_next(line, position);
	if (!ft_isdigit(line[*position]))
		return (-1);
	value = 0;
	started = 0;
	while (line[*position] && ft_isdigit(line[*position]))
	{
		value = value * 10 + (line[*position] - '0');
		started = 1;
		(*position)++;
	}
	if (!started || value < RGB_MIN || value > RGB_MAX)
		return (-1);
	return (value);
}

static int	parse_three_rgb_components(char *line, int start_pos, int *rgb)
{
	int	pos;
	int	component_idx;

	pos = start_pos;
	component_idx = 0;
	while (component_idx < RGB_COMPONENTS)
	{
		rgb[component_idx] = extract_single_rgb_value(line, &pos);
		if (rgb[component_idx] == -1)
			return (0);
		skip_whitespace_and_get_next(line, &pos);
		if (component_idx < RGB_COMPONENTS - 1)
		{
			if (line[pos] != ',')
				return (0);
			pos++;
		}
		component_idx++;
	}
	return (1);
}

static char	*locate_color_identifier_line(t_cub *game, char identifier)
{
	char	**config_lines;
	int		line_idx;
	int		i;

	if (!game->map->infos)
	{
		printf("Error: Missing map configuration.\n");
		ft_close_window(game);
	}
	config_lines = game->map->infos;
	line_idx = 0;
	while (config_lines[line_idx])
	{
		i = 0;
		while (config_lines[line_idx][i] == ' ' || config_lines[line_idx][i] == '\t')
			i++;
		if (config_lines[line_idx][i] == identifier
			&& (config_lines[line_idx][i + 1] == ' '
			|| config_lines[line_idx][i + 1] == '\t'))
			return (config_lines[line_idx]);
		line_idx++;
	}
	printf("Error: Color identifier '%c' not found.\n", identifier);
	ft_close_window(game);
	return (NULL);
}

typedef struct s_rgb_color
{
	unsigned int	*r;
	unsigned int	*g;
	unsigned int	*b;
}	t_rgb_color;

static void	process_color_line(t_cub *game, char id, t_rgb_color rgb)
{
	char	*line;
	int		rgb_values[RGB_COMPONENTS];
	int		pos;

	line = locate_color_identifier_line(game, id);
	pos = 0;
	while (line[pos] && line[pos] != id)
		pos++;
	if (line[pos] == id)
		pos++;
	if (!parse_three_rgb_components(line, pos, rgb_values))
	{
		printf("Error: Invalid RGB format for '%c'.\n", id);
		ft_close_window(game);
	}
	*rgb.r = rgb_values[0];
	*rgb.g = rgb_values[1];
	*rgb.b = rgb_values[2];
}

void	ceiling_color(t_cub *data)
{
	t_rgb_color	rgb = {&data->ceiling_rgb->r, &data->ceiling_rgb->g, &data->ceiling_rgb->b};
	process_color_line(data, 'C', rgb);
}

void	floor_color(t_cub *data)
{
	t_rgb_color	rgb = {&data->floor_rgb->r, &data->floor_rgb->g, &data->floor_rgb->b};
	process_color_line(data, 'F', rgb);
}
