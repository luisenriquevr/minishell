/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:23:41 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/29 18:20:51 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_and_close(int old, int new)
{
	if (old)
	{
		dup2(old, new);
		close(old);
	}
}

void	exec_error_exit(char *str1)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (ft_strncmp(str1, "./", 2))
		ft_putstr_fd("comand not found", STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_global.exit_status = 127;
	exit(g_global.exit_status);
}

void	set_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
