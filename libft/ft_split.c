/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nbariol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:35:53 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/29 13:23:17 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i);
}

static char	**ft_free(char ***str, int i)
{
	while (--i >= 0)
		free((*str)[i]);
	free(*str);
	return (0);
}

char	*malloc_word(const char *s, int *i, char c)
{
	char	*tab;
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (s[*i] == c && s[*i])
		(*i)++;
	while (s[*i + j] != c && s[*i + j])
		j++;
	tab = malloc(sizeof(char) * j + 1);
	if (!tab)
		return (NULL);
	while (k < j)
	{
		tab[k++] = s[*i];
		(*i)++;
	}
	tab[k] = 0;
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab2;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = count_word(s, c);
	if (!s)
		return (NULL);
	tab2 = malloc(sizeof(char *) * (len + 1));
	if (!tab2)
		return (NULL);
	while (i < len)
	{
		tab2[i] = malloc_word(s, &j, c);
		if (!tab2[i])
			return (ft_free(&tab2, i));
		i++;
	}
	tab2[i] = NULL;
	return (tab2);
}
