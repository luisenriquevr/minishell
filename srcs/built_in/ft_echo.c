/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:39 by lvarela           #+#    #+#             */
/*   Updated: 2022/02/24 13:07:38 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	n_checker(char **arg)
{
	int		i;
	int		j;
	int		pos;

	i = 0;
	j = 0;
	pos = 0;
	while (arg[i] && ft_strlen(arg[i]) >= 2)
	{
		if (arg[i][j] == '-' && arg[i][j + 1] == 'n')
		{
			j++;
			while (arg[i][j] == 'n')
				j++;
			if (j == (int)ft_strlen(arg[i]))
				pos++;
		}
		else
			return (pos);
		i++;
		j = 0;
	}
	return (pos);
}

// **arg ==> echo hola que tal		==>	hola que tal$
// **arg ==> echo -n hola que tal	==> hola que tal%
// **arg ==> echo -n -n -n -n hola	==> hola%
// **arg ==> echo -nnn -nnnnn hola	==> hola%
// **arg ==> echo -nnn -nnnnl hola	==> -nnnnl hola%
// **arg ==> echo -nnnnnl hola		==> -nnnnnl hola$
int	ft_echo(char **arg)
{
	int		i;
	int		n;

	i = 0;
	// Comprobamos flags -n y devolvemos cuantos hay para imprimir a partir de ahí
	n = n_checker(++arg);
	if (n > 0)
		i++;
	while (arg[n])
	{
		printf("%s", arg[n]);
		if (arg[n + 1])
			printf(" ");
		n++;
	}
	if (n == 0)
		printf("\n");
	return (0);
}
