/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:45:38 by lvarela           #+#    #+#             */
/*   Updated: 2022/04/14 20:13:09 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_checker(char **cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp("cd", cmd[0]))
		return (builtin_cd(cmd));
	else if (ft_strcmp("pwd", cmd[0]))
		return (builtin_pwd(cmd));
	if (ft_strcmp("exit", cmd[0]))
		return (builtin_exit(cmd));
	else if (ft_strcmp("echo", cmd[0]))
		return (builtin_echo(cmd));
	else if (ft_strcmp("env", cmd[0]))
		return (builtin_export(cmd));
	else if (ft_strcmp("export", cmd[0]))
		return (builtin_export(cmd));
	else if (ft_strcmp("unset", cmd[0]))
		return (builtin_unset(cmd));
	return (0);
}

// si returnea que lo es, tiene que hacerlo