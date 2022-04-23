/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:39:27 by lvarela           #+#    #+#             */
/*   Updated: 2022/04/23 16:36:35 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			builtin_env(char **cmd)
{
	int		i;

	i = 0;
	if (array_length(cmd) > 1)
		throw_error("Error: Too many arguments");
	while(global.env[i])
		printf("%s\n", global.env[i++]);
	return (1);
}

/*
int			print_export(char **cmd, int var)
{
	int		i;
	
	i = 0;

	if (var == 1 && array_length(cmd))
		throw_error("Error: Too many arguments");
	if (var == 1)
		printf("%s\n", global.env[i++]);
	else if (var == 2)
		printf("%s\n", global.export[i++]);
	return (1);

	*/