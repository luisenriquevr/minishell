/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:46:43 by cmarcu            #+#    #+#             */
/*   Updated: 2021/01/29 12:43:17 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memccpy(void *restrict dst, const void *restrict src, int c, size_t n)
{
	char	*srcchar;
	char	*dstchar;
	size_t	a;

	a = 0;
	srcchar = (char *)src;
	dstchar = (char *)dst;
	while (a < n)
	{
		dstchar[a] = srcchar[a];
		if (srcchar[a] == (char)c)
			return (dstchar + a + 1);
		a++;
	}
	return (NULL);
}
