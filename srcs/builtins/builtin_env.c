/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:39:27 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/27 18:33:15 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **cmd)
{
	int		i;

	i = 0;
	if (array_length(cmd) > 1)
		throw_error("Error: Too many arguments");
	while(global.env[i])
		printf("%s\n", global.env[i++]);
	return (1);
}
