/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:11:16 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/08 19:09:04 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_childs(int childs_counter)
{
	while (childs_counter-- > 0)
		waitpid(-1, &g_global.exit_status, 0);
}

static void	child_process(int fd[2], t_cmd_line *cmd, char **cmd_to_exec)
{
	set_signals();
	dup_and_close(cmd->fd_in, STDIN_FILENO);
	if (cmd->next != NULL)
	{
		if (cmd->fd_out)
			close(fd[WRITE_END]);
		else
			cmd->fd_out = fd[WRITE_END];
		close(fd[READ_END]);
	}
	dup_and_close(cmd->fd_out, STDOUT_FILENO);
	if (builtin_checker(cmd_to_exec))
		exit (g_global.exit_status);
	if (!access_checker(cmd_to_exec))
	{
		execve(cmd_to_exec[0], cmd_to_exec, g_global.env);
		g_global.exit_status = 127;
	}
	if (cmd_to_exec[0])
		exec_error_exit(cmd->to_exec[0]);
}

void	parent_process(int fd[2], t_cmd_line *cmd)
{
	if (cmd->next)
	{
		close(fd[WRITE_END]);
		if (!cmd->next->fd_in)
			cmd->next->fd_in = fd[READ_END];
		else
			close(fd[READ_END]);
	}
	if (cmd->fd_in)
	{
		close(cmd->fd_in);
		dup2(g_global.fd_stdin, STDIN_FILENO);
	}
	if (cmd->fd_out)
	{
		close(cmd->fd_out);
		dup2(g_global.fd_stdout, STDOUT_FILENO);
	}
}

int	maker(t_cmd_line	*tmp_cmd, int *fd, int *childs_counter)
{
	pid_t		pid;

	pid = fork();
	if (pid < 0)
		return (0);
	else if (!pid)
		child_process(fd, tmp_cmd, tmp_cmd->to_exec);
	else
		*childs_counter += 1;
	return (1);
}

int	exec_pipes(t_cmd_line *cmd)
{
	t_cmd_line	*tmp_cmd;
	int			fd[2];
	int			childs_counter;

	tmp_cmd = cmd;
	childs_counter = 0;
	while (tmp_cmd)
	{
		if (tmp_cmd->next && pipe(fd) < 0)
			return (throw_error("minishell: error: pipe"));
		if (tmp_cmd->exec && !maker(tmp_cmd, fd, &childs_counter))
			return (throw_error("minishell: error: fork"));
		parent_process(fd, tmp_cmd);
		tmp_cmd = tmp_cmd->next;
	}
	wait_childs(childs_counter);
	return (0);
}
