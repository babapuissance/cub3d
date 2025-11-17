/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/10/31 10:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_door_character(char c)
{
	return (c == 'D' || c == 'F');
}

bool	map_checker(t_cub *data, char **map)
{
	if (!check_duplicate_identifiers(data))
		return (false);
	if (!infos_checker(data))
		return (false);
	if (!flood_fill_test(data, map))
		return (false);
	return (true);
}
