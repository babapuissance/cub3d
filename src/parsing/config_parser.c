/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:44:20 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:48:22 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	identifiers_are_same(char *id1, char *id2)
{
	return (ft_strcmp(id1, id2) == 0);
}

static bool	scan_for_duplicate(char **infos, int current_idx)
{
	char	**current_tokens;
	char	**check_tokens;
	int		check_idx;

	current_tokens = split_on_space_tab(infos[current_idx]);
	if (!current_tokens)
		return (false);
	check_idx = current_idx + 1;
	while (infos[check_idx])
	{
		if (!is_line_empty(infos[check_idx]))
		{
			check_tokens = split_on_space_tab(infos[check_idx]);
			if (!check_tokens)
				return (ft_free(current_tokens), false);
			if (identifiers_are_same(current_tokens[0], check_tokens[0]))
				return (ft_free(check_tokens), ft_free(current_tokens), false);
			ft_free(check_tokens);
		}
		check_idx++;
	}
	ft_free(current_tokens);
	return (true);
}

bool	check_duplicate_identifiers(t_cub *data)
{
	int	line_idx;

	line_idx = 0;
	while (data->map->infos[line_idx])
	{
		if (!scan_for_duplicate(data->map->infos, line_idx))
			return (false);
		line_idx++;
	}
	return (true);
}

static bool	validate_single_config_line(char *line)
{
	char	**tokens;
	bool	result;

	if (is_line_empty(line))
		return (true);
	tokens = split_on_space_tab(line);
	if (!tokens)
		return (false);
	result = is_valid_identifier(tokens[0]);
	ft_free(tokens);
	return (result);
}

bool	infos_checker(t_cub *data)
{
	int	line_idx;

	line_idx = 0;
	while (data->map->infos[line_idx])
	{
		if (!validate_single_config_line(data->map->infos[line_idx]))
			return (false);
		line_idx++;
	}
	return (true);
}
