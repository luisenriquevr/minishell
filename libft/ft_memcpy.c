/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:15:20 by lvarela           #+#    #+#             */
/*   Updated: 2021/11/12 14:15:21 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	p1 = (unsigned char *)src;
	p2 = (unsigned char *)dst;
	i = 0;
	if (!n || src == dst)
		return (dst);
	while (i < n)
	{
		p2[i] = p1[i];
		i++;
	}
	return (dst);
}
