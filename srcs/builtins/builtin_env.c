/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:39:27 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/03 20:08:00 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **cmd)
{
	int		i;

	i = 0;
	if (array_length(cmd) > 1)
		throw_error("Error: Too many arguments");
	while (g_global.env[i])
		printf("%s\n", g_global.env[i++]);
	return (1);
}
