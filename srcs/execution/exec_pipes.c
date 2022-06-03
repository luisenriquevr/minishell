/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:11:16 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/03 20:32:01 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error_exit(char *str1, char *str2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
}

void	child_process(int fd[2], t_cmd_line *cmd, char **cmd_to_exec)
{
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
	access_checker(cmd_to_exec);
	execve(cmd_to_exec[0], cmd_to_exec, g_global.env);
	put_error_exit(cmd->to_exec[0], ": command not found\n");
	exit(g_global.exit_status);
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

int	exec_pipes(t_cmd_line *cmd)
{
	t_cmd_line	*tmp_cmd;
	int			fd[2];
	pid_t		pid;
	int			childs_counter;

	tmp_cmd = cmd;
	childs_counter = 0;
	while (tmp_cmd && *g_global.env)
	{
		if (tmp_cmd->next && pipe(fd) < 0)
			return (throw_error("minishell: error: pipe"));
		if (tmp_cmd->exec)
		{
			pid = fork();
			if (!pid)
				child_process(fd, tmp_cmd, tmp_cmd->to_exec);
			else if (pid)
				childs_counter++;
			else
				return (throw_error("minishell: error: fork"));
		}
		parent_process(fd, tmp_cmd);
		tmp_cmd = tmp_cmd->next;
	}
	while (childs_counter-- > 0)
		waitpid(-1, &g_global.exit_status, 0);
	return (0);
}