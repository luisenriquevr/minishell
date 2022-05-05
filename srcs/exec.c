/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:28:09 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/05 16:30:56 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(int fd_in, int fd[2], t_cmd_line *cmd, char **cmd_to_exec)
{
	// hay que recoger señales
	dup2(fd_in, STDIN_FILENO);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (cmd->next != NULL)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		close(fd[READ_END]);
	}
	if (builtin_checker(cmd_to_exec)) // aqui no comprobamos un builtin con path ?
		exit (global.exit_status); // lo hacemos directamente en la comprobacion
	access_checker(cmd_to_exec);
	execve(cmd_to_exec[0], cmd_to_exec, global.env);
	throw_error("Error: execution\n");
	exit(global.exit_status); // gestion de errores 
}

void	parent_process(int fd[2], int *fd_in, t_cmd_line *next)
{
	if (*fd_in > 0)
		close(*fd_in);
	if (next)
		close(fd[WRITE_END]);
	*fd_in = fd[READ_END];
}

int	exec_pipes(t_cmd_line *cmd)
{
	t_cmd_line	*tmp_cmd;
	int			fd[2];
	pid_t		pid;
	int			fd_in;

	// recoger señales y no hacer nada (funcion signal)
	tmp_cmd = cmd;
	fd_in = STDIN_FILENO;
	global.contador = 0;
	while (tmp_cmd)
	{
		// if (tmp_cmd->exec == false)
		// 	tmp_cmd = tmp_cmd->next;
		if (tmp_cmd->next && pipe(fd) < 0)
			return (throw_error("Error: pipe error\n")); // gestion de errores
		if (tmp_cmd->exec)
		{
			pid = fork();
			if (!pid)
				child_process(fd_in, fd, tmp_cmd, tmp_cmd->to_exec);
			else if (pid)
				global.contador++;
				// contar subprocesos
			else
				return (throw_error("Error: fork error\n")); // gestion de errores
		}		
		parent_process(fd, &fd_in, cmd->next);
		tmp_cmd = tmp_cmd->next;
	}
	// aqui conn un while poner el pid = -1 para que espere a cualquier proceso hijo hasta que se cierren todos
	while (global.contador-- > 0)
	{
		waitpid(-1, &global.exit_status, 0);
	}
	return (0);
}

int	exec_simple(char **cmd_to_exec)
{
	pid_t	pid;

	// aqui deberiamos de recoger señales y no hacer nada (func signal)
	if (builtin_checker(cmd_to_exec)) // aqui no comprobamos un builtin con path ?
		return (0);
	if (!access_checker(cmd_to_exec)) // comprobamos acceso con y sin path
		return (1); // error
	pid = fork();
	if (!pid)
	{
		execve(cmd_to_exec[0], cmd_to_exec, global.env); // tiene un exit dentro, si se hace sale
		perror("Error: execution\n"); // gestion de errores
		exit(1); // gestion de errores
	}
	else if (pid)
		waitpid(pid, &global.exit_status, 0); // en vez de NULL deberiamos de pasar &global.exit_status
	else
		perror("Error: fork\n"); // gestion de errores
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
	//if (*cmd_line->to_exec == NULL) // con esto se rompe si despues de hacer export a=2 hacemos export
	//	return (global.exit_status); // gestion de errores
	if (!cmd_line->next)
		return (exec_simple(cmd_line->to_exec));
	else
		return (exec_pipes(cmd_line));
	return (0);
}
