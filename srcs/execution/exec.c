/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:28:09 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/24 15:58:22 by lvarela          ###   ########.fr       */
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
		exit (global.exit_status);
	access_checker(cmd_to_exec);
	execve(cmd_to_exec[0], cmd_to_exec, global.env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->to_exec[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(global.exit_status);
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
		dup2(global.fd_stdin, STDIN_FILENO);
	}
	if (cmd->fd_out)
	{
		close(cmd->fd_out);
		dup2(global.fd_stdout, STDOUT_FILENO);
	}
}

int		exec_pipes(t_cmd_line *cmd)
{
	t_cmd_line	*tmp_cmd;
	int			fd[2];
	pid_t		pid;
	int			childs_counter;

	tmp_cmd = cmd;
	childs_counter = 0;
	while (tmp_cmd && *global.env)
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
		waitpid(-1, &global.exit_status, 0);
	return (0);
}

int	exec_simple(t_cmd_line *cmd)
{
	pid_t	pid;

	dup_and_close(cmd->fd_in, STDIN_FILENO);
	dup_and_close(cmd->fd_out, STDOUT_FILENO);
	if (cmd->head_token->type == BUILTIN)
		builtin_checker(cmd->to_exec);
	else if (*global.env)
	{
		access_checker(cmd->to_exec);
		pid = fork();
		if (!pid)
		{
			execve(cmd->to_exec[0], cmd->to_exec, global.env);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->to_exec[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(1); // gestion de errores
		}
		else if (pid)
			waitpid(pid, &global.exit_status, 0);
		else
			perror("minishell: error: fork");
	}
	if (cmd->fd_in)
		dup2(global.fd_stdin, STDIN_FILENO);
	if (cmd->fd_out)
		dup2(global.fd_stdout, STDOUT_FILENO);
	return (0);
}

int	exec(t_cmd_line *cmd_line)
{
	if (!cmd_line)
		return (global.exit_status); // gestion de errores
	if (!cmd_line->next)
		return (exec_simple(cmd_line));
	else
		return (exec_pipes(cmd_line));
	return (0);
}
