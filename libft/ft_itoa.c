/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:46:43 by cmarcu            #+#    #+#             */
/*   Updated: 2021/02/05 09:47:35 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_length(int n)
{
	int length;

	length = 0;
	if (n < 0)
		length++;
	if (n == 0)
		length = 1;
	while (n != 0)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		length;

	length = itoa_length(n);
	if (!(str = (char *)malloc(sizeof(*str) * (length + 1))))
		return (NULL);
	str[length] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str[length-- - 1] = '8';
			n = n / 10;
		}
		n = -n;
	}
	if (n == 0)
		str[0] = '0';
	while (length >= 0 && n != 0)
	{
		str[length-- - 1] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
