/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:33:39 by cmarcu            #+#    #+#             */
/*   Updated: 2021/01/29 10:41:49 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *result;

	if (!(result = (t_list *)malloc(sizeof(*result))))
		return (NULL);
	result->content = content;
	result->next = NULL;
	return (result);
}
