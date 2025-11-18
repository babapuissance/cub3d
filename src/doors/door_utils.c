/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:00:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 17:00:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	check_all_doors_open(t_cub *data)
{
	int	i;

	if (!data || !data->doors || data->door_count == 0)
		return (false);
	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].is_closed == 1)
			return (false);
		i++;
	}
	return (true);
}
