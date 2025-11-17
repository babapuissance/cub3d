/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nbariol-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:15:21 by nbariol-          #+#    #+#             */
/*   Updated: 2024/12/05 12:34:04 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	t_list	*del_node(t_list *map, void (*del)(void *))
{
	if (map)
		ft_lstclear(&map, del);
	return (NULL);
}

static	t_list	*mapi(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*new_node;
	void	*content;

	map = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
		{
			return (del_node(map, del));
		}
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			del(content);
			return (del_node(map, del));
		}
		ft_lstadd_back(&map, new_node);
		lst = lst->next;
	}
	return (map);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	if (!lst || !f || !del)
		return (NULL);
	return (mapi(lst, f, del));
}
