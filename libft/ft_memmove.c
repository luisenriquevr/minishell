/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:15:25 by lvarela           #+#    #+#             */
/*   Updated: 2021/11/12 14:15:26 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)src;
	p2 = (unsigned char *)dst;
	if (p1 == 0 && p2 == 0)
		return (NULL);
	if (p1 > p2)
	{
		while (len-- > 0)
			*p2++ = *p1++;
	}
	else
	{
		while (len-- > 0)
			p2[len] = p1[len];
	}
	return (dst);
}
