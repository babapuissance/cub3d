/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:01 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 13:48:37 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**split_on_space_tab(char const *s)
{
	char	**result;
	char	*temp;
	size_t	i;

	if (!s)
		return (NULL);
	temp = ft_strdup(s);
	if (!temp)
		return (NULL);
	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\t')
			temp[i] = ' ';
		i++;
	}
	result = ft_split(temp, ' ');
	free(temp);
	return (result);
}

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

bool	is_correct_extension(char *filename, char *ext)
{
	char	*dot_position;
	int		file_idx;
	int		ext_idx;

	dot_position = ft_strrchr(filename, '.');
	if (!dot_position || dot_position[0] == '\0')
		return (false);
	file_idx = 1;
	ext_idx = 0;
	while (dot_position[file_idx] && ext[ext_idx]
		&& dot_position[file_idx] == ext[ext_idx])
	{
		file_idx++;
		ext_idx++;
	}
	return (ext[ext_idx] == '\0' && dot_position[file_idx] == '\0');
}

bool	is_line_empty(char *line)
{
	int	idx;

	if (line[0] == '\n')
		return (true);
	idx = 0;
	while (line[idx])
	{
		if (line[idx] != ' ' && line[idx] != '\t' && line[idx] != '\n')
			return (false);
		idx++;
	}
	return (true);
}

bool	is_valid_identifier(char *line)
{
	char	**parsed;
	bool	is_valid;

	parsed = split_on_space_tab(line);
	if (!parsed)
		return (false);
	if (ft_strlen(parsed[0]) > 2)
	{
		ft_free(parsed);
		return (false);
	}
	is_valid = (ft_strncmp(parsed[0], "NO", 3) == 0 || ft_strncmp(parsed[0],
				"SO", 3) == 0 || ft_strncmp(parsed[0], "WE", 3) == 0
			|| ft_strncmp(parsed[0], "EA", 3) == 0 || ft_strncmp(parsed[0], "F",
				2) == 0 || ft_strncmp(parsed[0], "C", 2) == 0
			|| ft_strncmp(parsed[0], "FT", 3) == 0 || ft_strncmp(parsed[0],
				"CT", 3) == 0);
	ft_free(parsed);
	return (is_valid);
}
