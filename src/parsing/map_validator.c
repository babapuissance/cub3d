/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:44:53 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:48:32 by sle-bail         ###   ########.fr       */
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
