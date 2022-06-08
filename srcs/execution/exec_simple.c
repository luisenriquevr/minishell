/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:11:14 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/08 18:49:00 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_cmd_line *cmd)
{
	set_signals();
	if (cmd->exec && !access_checker(cmd->to_exec))
	{
		execve(cmd->to_exec[0], cmd->to_exec, g_global.env);
		g_global.exit_status = 127;
	}
	if (cmd->exec && cmd->to_exec[0])
		exec_error_exit(cmd->to_exec[0]);
	exit (g_global.exit_status);
}

int	exec_simple(t_cmd_line *cmd)
{
	pid_t	pid;

	dup_and_close(cmd->fd_in, STDIN_FILENO);
	dup_and_close(cmd->fd_out, STDOUT_FILENO);
	if (cmd->head_token->type == BUILTIN)
		builtin_checker(cmd->to_exec);
	else
	{
		pid = fork();
		if (!pid)
			child_process(cmd);
		else if (pid)
			waitpid(-1, &g_global.exit_status, 0);
		else
			perror("minishell: error: fork");
	}
	if (cmd->fd_in)
		dup2(g_global.fd_stdin, STDIN_FILENO);
	if (cmd->fd_out)
		dup2(g_global.fd_stdout, STDOUT_FILENO);
	return (0);
}
