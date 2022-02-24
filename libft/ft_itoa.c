/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:14:04 by lvarela           #+#    #+#             */
/*   Updated: 2021/11/12 14:14:05 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		++i;
	}
	return (i);
}

static char	*ft_fulfill(int n, int i)
{
	char	*str;
	long	nbr;

	nbr = n;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!(str))
		return (NULL);
	str[i] = '\0';
	i--;
	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	while (nbr > 9)
	{
		str[i--] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	if (nbr < 10)
		str[i--] = (nbr % 10) + '0';
	if (n < 0)
		str[i--] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		i;

	if (n == -2147483648)
	{
		ptr = (char *)malloc(sizeof(char) * 12);
		if (!(ptr))
			return (NULL);
		ft_strlcpy(ptr, "-2147483648", 12);
		return (ptr);
	}
	i = ft_getlen(n);
	ptr = ft_fulfill(n, i);
	return (ptr);
}
