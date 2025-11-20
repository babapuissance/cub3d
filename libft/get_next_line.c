/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nbariol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/14 00:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

static char	*handle_eof(char *line, int line_size)
{
	if (line_size == 0)
	{
		free(line);
		return (NULL);
	}
	line[line_size] = '\0';
	return (line);
}

static char	*expand_line(char *line)
{
	char	*temp;

	temp = malloc(BUFFER_SIZE * 2);
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	ft_strlcpy(temp, line, BUFFER_SIZE);
	free(line);
	return (temp);
}

static char	*process_char(char *line, char *buf, int *ls, int *bi)
{
	if (buf[*bi] == '\n')
		return (line[*ls] = '\n', (*bi)++, line[++(*ls)] = '\0', line);
	if (*ls + 1 >= BUFFER_SIZE)
	{
		line = expand_line(line);
		if (!line)
			return (NULL);
	}
	line[(*ls)++] = buf[(*bi)++];
	return (line);
}

static char	*gnl_loop(char *buffer, int *buffer_idx, int *bytes_read, int fd)
{
	char	*line;
	int		line_size;

	line = malloc(BUFFER_SIZE);
	if (!line)
		return (NULL);
	line_size = 0;
	while (1)
	{
		if (*buffer_idx >= *bytes_read)
		{
			*bytes_read = read(fd, buffer, BUFFER_SIZE);
			*buffer_idx = 0;
			if (*bytes_read <= 0)
				return (handle_eof(line, line_size));
		}
		line = process_char(line, buffer, &line_size, buffer_idx);
		if (!line || (line_size > 0 && line[line_size - 1] == '\n'))
			return (line);
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_idx = 0;
	static int	bytes_read = 0;

	if (fd < 0)
		return (NULL);
	return (gnl_loop(buffer, &buffer_idx, &bytes_read, fd));
}
