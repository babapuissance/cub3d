/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_analyzer_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:20:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 19:20:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*skip_to_next_line(char *str)
{
	int	position;

	if (!ft_strchr(str, '\n'))
		return (NULL);
	position = 0;
	while (str[position] && str[position] != '\n')
		position++;
	return (str + position);
}

int	end_of_spaces_index(char *line)
{
	int	position;

	position = 0;
	while (line[position] && (line[position] == ' ' || line[position] == '\t'))
		position++;
	return (position);
}
