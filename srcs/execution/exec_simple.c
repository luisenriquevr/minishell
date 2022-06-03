/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:11:14 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/03 20:39:13 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_simple(t_cmd_line *cmd)
{
	pid_t	pid;

	dup_and_close(cmd->fd_in, STDIN_FILENO);
	dup_and_close(cmd->fd_out, STDOUT_FILENO);
	if (cmd->head_token->type == BUILTIN)
		builtin_checker(cmd->to_exec);
	else if (*g_global.env)
	{
		access_checker(cmd->to_exec);
		pid = fork();
		if (!pid)
		{
			execve(cmd->to_exec[0], cmd->to_exec, g_global.env);
			exec_error_exit(cmd->to_exec[0], ": command not found\n");
		}
		else if (pid)
			waitpid(pid, &g_global.exit_status, 0);
		else
			perror("minishell: error: fork");
	}
	if (cmd->fd_in)
		dup2(g_global.fd_stdin, STDIN_FILENO);
	if (cmd->fd_out)
		dup2(g_global.fd_stdout, STDOUT_FILENO);
	return (0);
}
