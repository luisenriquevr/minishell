/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:43:13 by cmarcu            #+#    #+#             */
/*   Updated: 2021/02/05 09:48:55 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_mountarray(char const *s, char c)
{
	size_t	result;
	char	*aux;
	char	**array;

	result = 0;
	aux = (char*)s;
	while (*aux)
	{
		while (*aux == c)
			aux++;
		if (*aux != '\0')
			result++;
		while (*aux && *aux != c)
			aux++;
	}
	if (!(array = (char **)malloc((result + 1) * sizeof(char *))))
		return (NULL);
	return (array);
}

char		**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (!(array = ft_mountarray(s, c)))
		return (NULL);
	i = 0;
	j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			while (s[j] && s[j] != c)
				j++;
			array[i++] = ft_substr(s, 0, j);
			s = s + j;
		}
		j = 0;
	}
	array[i] = NULL;
	return (array);
}
