/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cf_colors_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:45:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/20 20:45:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define RGB_MIN 0
#define RGB_MAX 255

int	skip_whitespace_and_get_next(char *str, int *idx)
{
	while (str[*idx] && (str[*idx] == ' ' || str[*idx] == '\t'))
		(*idx)++;
	return (str[*idx]);
}

int	extract_single_rgb_value(char *line, int *position)
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
