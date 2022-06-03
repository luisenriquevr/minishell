/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:39 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/03 20:04:41 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_checker(char **cmd)
{
	int		i;
	int		j;
	int		pos;

	i = 0;
	j = 0;
	pos = 0;
	while (cmd[i] && ft_strlen(cmd[i]) >= 2)
	{
		if (cmd[i][j] == '-' && cmd[i][j + 1] == 'n')
		{
			j++;
			while (cmd[i][j] == 'n')
				j++;
			if (j == (int)ft_strlen(cmd[i]))
				pos++;
		}
		else
			return (pos);
		i++;
		j = 0;
	}
	return (pos);
}

int	builtin_echo(char **cmd)
{
	int		i;
	int		n;

	i = 0;
	n = n_checker(++cmd);
	if (n > 0)
		i++;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
	g_global.exit_status = 0;
	return (1);
}
