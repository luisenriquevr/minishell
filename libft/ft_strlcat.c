/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:16:37 by lvarela           #+#    #+#             */
/*   Updated: 2021/11/12 14:16:38 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	k = 0;
	if (i <= dstsize)
		j = j + i;
	else
		j = j + dstsize;
	while (src[k] && i + 1 < dstsize)
	{
		dst[i] = src[k];
		k++;
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	return (j);
}
