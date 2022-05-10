/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:28:09 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/09 12:13:13 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Esta funcion nos viene bien para ahorrar lineas, a falta de probar. */
/*
void	dup_and_close(int old, int new)
{
	dup2(old, new);
	close(old);
}
*/

void	child_process(int fd[2], t_cmd_line *cmd, char **cmd_to_exec)
{
	// hay que recoger señales
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->next != NULL)
	{
		if (cmd->fd_out)
			close(fd[WRITE_END]);
		else
			cmd->fd_out = fd[WRITE_END];
		close(fd[READ_END]);
	}
	if (cmd->fd_out)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	if (builtin_checker(cmd_to_exec)) // aqui no comprobamos un builtin con path ?
		exit (global.exit_status);
	access_checker(cmd_to_exec);
	execve(cmd_to_exec[0], cmd_to_exec, global.env);
	throw_error("Error: execution\n");
	exit(global.exit_status);
}

void	parent_process(int fd[2], t_cmd_line *cmd)
{
	if (cmd->fd_in > 0)
		close(cmd->fd_in);
	if (cmd->next)
	{
		close(fd[WRITE_END]);
		if (!cmd->next->fd_in)
			cmd->next->fd_in = fd[READ_END];
		else
			close(fd[READ_END]);
	}
}

int		exec_pipes(t_cmd_line *cmd)
{
	t_cmd_line	*tmp_cmd;
	int			fd[2];
	pid_t		pid;

	// recoger señales y no hacer nada (funcion signal)
	tmp_cmd = cmd;
	global.contador = 0;
	while (tmp_cmd)
	{
		if (tmp_cmd->next && pipe(fd) < 0)
			return (throw_error("Error: pipe error\n"));
		if (tmp_cmd->exec)
		{
			pid = fork();
			if (!pid)
				child_process(fd, tmp_cmd, tmp_cmd->to_exec);
			else if (pid)
				global.contador++;
			else
				return (throw_error("Error: fork error\n"));
		}
		parent_process(fd, tmp_cmd);
		tmp_cmd = tmp_cmd->next;
	}
	// aqui conn un while poner el pid = -1 para que espere a cualquier proceso hijo hasta que se cierren todos
	while (global.contador-- > 0)
		waitpid(-1, &global.exit_status, 0);
	return (0);
}
int	exec_simple(t_cmd_line *cmd)
{
	pid_t	pid;
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	// aqui deberiamos de recoger señales y no hacer nada (func signal)
	if (cmd->head_token->type == BUILTIN)
	{
		builtin_checker(cmd->to_exec); // aqui no comprobamos un builtin con path ?
		if (cmd->fd_in)
			dup2(global.fd_stdin, STDIN_FILENO);
		if (cmd->fd_out)
			dup2(global.fd_stdout, STDOUT_FILENO);
		return (0);
	}
	if (access_checker(cmd->to_exec)) // comprobamos acceso con y sin path
		return (1); // error
	pid = fork();
	if (!pid)
	{
		execve(cmd->to_exec[0], cmd->to_exec, global.env); // tiene un exit dentro, si se hace sale
		perror("Error: execution\n");
		exit(1); // gestion de errores
	}
	else if (pid)
		waitpid(pid, &global.exit_status, 0); // en vez de NULL deberiamos de pasar &global.exit_status
	else
		perror("Error: fork\n");
	if (cmd->fd_in)
		dup2(global.fd_stdin, STDIN_FILENO);
	if (cmd->fd_out)
		dup2(global.fd_stdout, STDOUT_FILENO);
	return (0);
}
/*
** La variable enviroment la podiamos meter en la global pero luego
** quizás tendremos problemas para el tema del shell level (SHLVL)
*/
// TODO => cat | ls no funciona se queda en bucle infinito
// Por lo que he probado la parte de exec_simple la podemos eliminar =) ==> A falta de probarlo bien
int	exec(t_cmd_line *cmd_line)
{
	if (!cmd_line) // con esto se rompe si despues de hacer export a=2 hacemos export
		return (global.exit_status); // gestion de errores
	if (!cmd_line->next)
		return (exec_simple(cmd_line));
	else
		return (exec_pipes(cmd_line));
	return (0);
}
