/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:44:49 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:48:30 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	validate_argument_count(t_cub *data, int argc)
{
	if (argc != 2)
	{
		printf("Use the program as follows: ./cub3d file.cub");
		free(data);
		exit(1);
	}
}

static char	*extract_file_extension(char *filepath)
{
	char	*extension;

	extension = ft_strrchr(filepath, '.');
	if (!extension || extension[0] == '\0')
		return (NULL);
	return (extension + 1);
}

static bool	strings_match(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] == '\0' && str2[i] == '\0');
}

static void	validate_file_extension(t_cub *data, char *filepath)
{
	char	*extension;

	extension = extract_file_extension(filepath);
	if (!extension || !strings_match(extension, "cub"))
	{
		printf("Invalid file extension. Use .cub files only.\n");
		free(data);
		exit(1);
	}
}

void	arg_check(t_cub *data, int argc, char **argv)
{
	validate_argument_count(data, argc);
	validate_file_extension(data, argv[1]);
}
