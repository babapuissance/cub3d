/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nbariol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:34:41 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/29 13:18:12 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_sep(char c, const char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && is_sep(s1[i], set) == 1)
		i++;
	start = i;
	end = ft_strlen(s1);
	while (end > 0 && is_sep(s1[end - 1], set))
		end--;
	if (start >= end)
		return (ft_strdup(""));
	str = malloc((end - start + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
/*
int	main(int argc, char **argv)
{
	printf("the result is %s", ft_strtrim(argv[1], argv[2]));
	return(0);
}
*/
