/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:27:07 by cmarcu            #+#    #+#             */
/*   Updated: 2021/01/29 11:22:36 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*a;
	size_t	i;

	if (!(a = (char *)malloc(count * size)))
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		a[i] = 0;
		i++;
	}
	return ((void *)a);
}
