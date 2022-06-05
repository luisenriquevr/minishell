/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:51 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/05 20:20:45 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **cmd)
{
	if (array_length(cmd) > 2)
		return (throw_error_exit_status("minishell: \
			exit: too many arguments", 1, 1));
	printf("exit\n");
	if (array_length(cmd) == 2 && !ft_isdigit(cmd[1][0]))
	{
		ft_putendl_fd("minishell: \
			exit: numeric argument required", STDERR_FILENO);
		exit(255);
	}
	if (array_length(cmd) < 2)
		exit(EXIT_SUCCESS);
	else
		exit(ft_atoi(cmd[1]));
	return (1);
}
