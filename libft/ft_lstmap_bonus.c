/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:14:49 by lvarela           #+#    #+#             */
/*   Updated: 2021/11/12 14:14:50 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*map;
	t_list	*tmp;

	if (lst)
	{
		tmp = lst;
		new = ft_lstnew(f(tmp->content));
		if (!(new))
			return (NULL);
		tmp = tmp->next;
		while (tmp)
		{
			map = ft_lstnew(f(tmp->content));
			if (!(map))
			{
				ft_lstclear(&new, del);
				return (NULL);
			}
			ft_lstadd_back(&new, map);
			tmp = tmp->next;
		}
		return (new);
	}
	return (NULL);
}
