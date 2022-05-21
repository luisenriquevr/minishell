/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:22:06 by cmarcu            #+#    #+#             */
/*   Updated: 2022/05/21 16:13:39 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	a;
	size_t	length;

	length = ft_strlen(s);
	a = 0;
	while (a <= length)
	{
		if (s[a] == (char)c)
			return ((char *)(s + a));
		a++;
	}
	return (NULL);
}
