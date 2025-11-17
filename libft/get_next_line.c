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

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_idx = 0;
	static int	bytes_read = 0;
	char		*line;
	int			line_size;
	char		*temp;

	if (fd < 0)
		return (NULL);
	line = malloc(BUFFER_SIZE);
	if (!line)
		return (NULL);
	line_size = 0;
	while (1)
	{
		if (buffer_idx >= bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			buffer_idx = 0;
			if (bytes_read <= 0)
			{
				if (line_size == 0)
				{
					free(line);
					return (NULL);
				}
				line[line_size] = '\0';
				return (line);
			}
		}
		if (buffer[buffer_idx] == '\n')
		{
			line[line_size++] = '\n';
			buffer_idx++;
			line[line_size] = '\0';
			return (line);
		}
		if (line_size + 1 >= BUFFER_SIZE)
		{
			temp = malloc(BUFFER_SIZE * 2);
			if (!temp)
			{
				free(line);
				return (NULL);
			}
			ft_strlcpy(temp, line, BUFFER_SIZE);
			free(line);
			line = temp;
		}
		line[line_size++] = buffer[buffer_idx++];
	}
	return (line);
}
