/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:17:15 by lvarela           #+#    #+#             */
/*   Updated: 2021/11/12 14:17:16 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char const *str, char const *to_find)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[j])
	{
		k = 0;
		while (to_find[k])
		{
			if (str[i] == to_find[k])
				i++;
			if (str[i] != to_find[k])
				k++;
		}
		j++;
	}
	return (i);
}

static int	ft_end(char const *str, char const *to_find)
{
	int	i;
	int	j;
	int	k;
	int	o;

	i = (int)ft_strlen(str) - 1;
	j = 0;
	k = 0;
	o = 0;
	while (str[o])
	{
		while (to_find[k])
		{
			if (str[i - j] == to_find[k])
			{
				j++;
				k = 0;
			}
			if (str[i - j] != to_find[k])
				k++;
		}
		o++;
	}
	return (j);
}

static char	*ft_tobetrim(char const *s1, int start, int end)
{
	int		x;
	char	*ptr;

	x = 0;
	ptr = (char *)malloc(sizeof(char)
			* (int)ft_strlen(s1) + 1 - (start + end));
	if (!(ptr))
		return (NULL);
	while (start <= ((int)ft_strlen(s1) - end - 1))
		ptr[x++] = s1[start++];
	ptr[x] = '\0';
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (s1 == NULL)
		return (NULL);
	if (s1[0] == '\0' || set == NULL)
		return (ft_strdup(s1));
	start = ft_start(s1, set);
	if (start == (int)ft_strlen(s1))
		return (ft_strdup(""));
	end = ft_end(s1, set);
	return (ft_tobetrim(s1, start, end));
}
