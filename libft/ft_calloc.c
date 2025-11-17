/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nbariol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:03:45 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/29 13:17:22 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_size;
	size_t			i;
	void			*ptr;
	unsigned char	*copy_byte;

	i = 0;
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	copy_byte = (unsigned char *)ptr;
	while (i < total_size)
	{
		copy_byte[i] = 0;
		i++;
	}
	return (ptr);
}
