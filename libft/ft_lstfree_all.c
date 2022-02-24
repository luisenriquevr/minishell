/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:14:32 by lvarela           #+#    #+#             */
/*   Updated: 2021/11/12 14:18:37 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree_all(t_list **lst)
{
	t_list	*ptr;

	ptr = *lst;
	if (lst)
	{
		while (*lst)
		{
			ptr = (*lst)->next;
			free((*lst));
			(*lst) = ptr;
		}
	}
}
