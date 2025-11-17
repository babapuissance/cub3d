/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nbariol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:55:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/29 13:21:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	c1;

	c1 = (unsigned char)c;
	i = 0;
	while (s[i])
		i++;
	while (i > 0 || (i == 0 && s[i] == c1))
	{
		if (c1 == s[i])
			return ((char *)&s[i]);
		if (i > 0)
			i--;
	}
	return (NULL);
}
