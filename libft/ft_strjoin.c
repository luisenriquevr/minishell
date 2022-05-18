/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:38:54 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/18 16:39:03 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*ptr;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	k = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(ptr = (char *)malloc(sizeof(char) * ((sizeof(char) * k)))))
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i] != '\0')
		ptr[i] = s1[i];
	while (s2[++j] != '\0')
		ptr[i++] = s2[j];
	ptr[i] = '\0';
	return (ptr);
}