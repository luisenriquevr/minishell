/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:28:09 by lvarela           #+#    #+#             */
/*   Updated: 2022/04/13 15:02:05 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define READ_END	0
#define WRITE_END	1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;


void	child_process(int fd_in, int fd[2], t_cmd_line *cmd, char **cmd_to_exec, char **envp)
{
	dup2(fd_in, STDIN_FILENO);
	if (cmd->next != NULL)
		dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[READ_END]);
	if (builtin_checker(cmd_to_exec[0])) // aqui no comprobamos un builtin con path ?
		exit (0); // lo hacemos directamente en la comprobacion
	if (!access_checker(&cmd_to_exec[0], envp)) // comprobamos acceso con y sin path
		exit (1); // error
	execve(cmd_to_exec[0], cmd_to_exec, envp);
	throw_error("Error: execution\n");
	exit(1); // gestion de errores 
}

void	parent_process(pid_t pid, int fd[2], int *fd_in)
{
	waitpid(pid, NULL, 0); // en vez del null debemos pasar el exit_status
	close(fd[WRITE_END]);
	*fd_in = fd[READ_END];
}

int		exec_pipes(t_cmd_line *cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		fd_in;
	t_cmd_line	*cmd;

	// recoger señales y no hacer nada (funcion signal)
	fd_in = 0;
	while (cmd)
	{
		if (pipe(fd) < 0)
			return (throw_error("Error: pipe error\n")); // gestion de errores
		pid = fork();
		if (!pid)
			child_process(fd_in, fd, cmd, cmd->to_exec, envp);
		else if (pid)
		{
			parent_process(pid, fd, &fd_in);
			cmd = cmd->next;
		}
		else
			return (throw_error("Error: fork error\n")); // gestion de errores
	}
	return (0);
}

int		exec_simple(char **cmd_to_exec, char **envp)
{
	pid_t	pid;

	// aqui deberiamos de recoger señales y no hacer nada (func signal)
	if (builtin_checker(cmd_to_exec[0])) // aqui no comprobamos un builtin con path ?
		return (0); // lo hacemos directamente en la comprobacion
	if (!access_checker(&cmd_to_exec[0], envp)) // comprobamos acceso con y sin path
		return (1); // error
	pid = fork();
	if (!pid)
	{
		execve(cmd_to_exec[0], cmd_to_exec, envp); // tiene un exit dentro, si se hace sale
		perror("Error: execution error\n"); // gestion de errores
		exit(1); // gestion de errores
	}
	else if (pid)
		waitpid(pid, NULL, 0); // en vez de NULL deberiamos de pasar &global.exit_status
	else
		perror("Error: fork\n"); // gestion de errores
	return (0);
}

/*
** La variable enviroment la podiamos meter en la global pero luego
** quizás tendremos problemas para el tema del shell level (SHLVL)
*/

int		exec(t_cmd_line *cmd, char **envp)
{
	if (!cmd)
		return (1); // gestion de errores
	if (!cmd->next)
		return (exec_simple(cmd->to_exec, envp));
	else
		return (exec_pipes(cmd, envp));
	return (0);
}
