/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:51 by lvarela           #+#    #+#             */
/*   Updated: 2022/04/15 13:02:31 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			builtin_exit(char **cmd)
{
	if (array_length(cmd) > 2)
		return (throw_error_exit_status("Error: Too many arguments", 1, 1));
	printf("exit\n");
	if (array_length(cmd) == 2 && !ft_isdigit(cmd[1][0])) // cambiar 
	{
		throw_error("Error: Bad expression");
		exit(255);
	}
	if (!cmd[1])
		exit(EXIT_SUCCESS);
	else
		exit(ft_atoi(cmd[1]));
	return (1);
}
