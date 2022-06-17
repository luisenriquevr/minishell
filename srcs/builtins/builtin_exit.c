/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:51 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/17 16:17:22 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_digits(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	while (cmd[i])
	{
		if (cmd[i] >= '0' && cmd[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	builtin_exit(char **cmd)
{
	if (array_length(cmd) > 2)
		return (throw_error_exit_status("minishell: \
			exit: too many arguments", 1, 1));
	printf("exit\n");
	if (array_length(cmd) == 2 && !only_digits(cmd[1]))
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
