/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:45:38 by lvarela           #+#    #+#             */
/*   Updated: 2022/03/07 15:52:44 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_checker(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp("cd", cmd))
		return (1);
	else if (ft_strcmp("pwd", cmd))
		return (1);
	if (ft_strcmp("exit", cmd))
		return (1);
	else if (ft_strcmp("echo", cmd))
		return (1);
	else if (ft_strcmp("env", cmd))
		return (1);
	else if (ft_strcmp("export", cmd))
		return (1);
	else if (ft_strcmp("unset", cmd))
		return (1);
	return (0);
}

// si returnea que lo es, tiene que hacerlo