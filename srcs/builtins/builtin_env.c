/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:39:27 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/13 18:06:58 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_env(char **cmd)
{
	int		i;

	i = 0;
	if (array_length(cmd) > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": Too many arguments\n");
	}
	else
		while(global.env[i])
			printf("%s\n", global.env[i++]);
	return (1);
}