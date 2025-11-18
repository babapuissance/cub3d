/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 18:30:00 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	get_minimap_rotation_from_spawn(char dir)
{
	if (dir == 'N')
		return (0.0);
	else if (dir == 'S')
		return (M_PI);
	else if (dir == 'E')
		return (M_PI / 2.0);
	else if (dir == 'W')
		return (-M_PI / 2.0);
	else
		return (0.0);
}
