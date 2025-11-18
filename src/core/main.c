/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:42:37 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:46:54 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_file(t_cub *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (0);
	}
	read_file_infos(data, fd);
	if (read_map_content(data, fd) == 0)
	{
		cleanup_remaining_lines(fd);
		close(fd);
		return (0);
	}
	cleanup_remaining_lines(fd);
	close(fd);
	return (1);
}

static int	validate_and_process_map(t_cub *data)
{
	if (!pos_nb_checker(data->map->map, data))
	{
		printf("INVALID MAP\n");
		free_data(data);
		return (0);
	}
	data->map->map_tab = ft_split(data->map->map, '\n');
	if (!data->map->map_tab)
		return (0);
	set_player_pos(data);
	return (1);
}

static int	handle_map_validation(t_cub *data)
{
	if (!map_checker(data, data->map->map_tab))
	{
		if (!check_duplicate_identifiers(data))
			printf("Duplicate identifiers found in map info.\n");
		else
			printf("INVALID MAP");
		ft_close_window(data);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub	*data;

	data = malloc(sizeof(t_cub));
	if (!data)
		return (1);
	arg_check(data, argc, argv);
	if (!data_init(data))
		return (free(data), (1));
	if (!parse_file(data, argv[1]))
		return (ft_close_window(data));
	if (!validate_and_process_map(data))
		return (1);
	handle_map_validation(data);
	initialize_game(data);
	run_game(data);
	free_data(data);
	return (0);
}
