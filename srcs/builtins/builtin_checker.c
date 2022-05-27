/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:45:38 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/27 19:44:38 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_checker(char **cmd)
{
	if (cmd[0] == NULL)
		return (0);
	if (!ft_strcmp("cd", cmd[0]))
		return (builtin_cd(cmd));
	else if (!ft_strcmp("pwd", cmd[0]))
		return (builtin_pwd(cmd));
	if (!ft_strcmp("exit", cmd[0]))
		return (builtin_exit(cmd));
	else if (!ft_strcmp("echo", cmd[0]))
		return (builtin_echo(cmd));
	else if (!ft_strcmp("env", cmd[0]))
		return (builtin_env(cmd));
	else if (!ft_strcmp("export", cmd[0]))
		return (builtin_export(cmd));
	else if (!ft_strcmp("unset", cmd[0]))
		return (builtin_unset(cmd));
	return (0);
}
