/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:36:17 by cmarcu            #+#    #+#             */
/*   Updated: 2022/04/22 19:14:59 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	copy_env(char **envp)
{
	char	**new_envp;
	int		i;

	new_envp = (char **)malloc(sizeof(char *) * global.env_len); //TODO: liberar en gestión de errores
	if (!new_envp)
		return (errcode_print_return(50, "Malloc error"));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	global.env = new_envp;
	return (0);
}

int	init_global(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	global.exit_status = 0;
	global.env_len = (i + 2);
	if (copy_env(env))
		return (50);
	global.env_export = NULL; //create_env_export(); Hasta que lo necesitemos
	global.fd_stdin = dup(STDIN_FILENO);
	global.fd_stdout = dup(STDOUT_FILENO);
	global.signal_status = 0;
	global.redir_error = 0;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char		*str;
	t_cmd_line	*cmd_line;

	cmd_line = NULL;
	if (argc != 1 || !argv)
	{
		print_error("Invalid arguments: try './minishell'");
		exit(EXIT_FAILURE);
	}
	if (init_global(env))
		exit(EXIT_FAILURE);
	printtitle();
	while (1)
	{
		str = readline("minishell $ ");
		add_history(str); //Esto añade la historia de comandos, hace que funcione la flecha para arriba
		if (check_str(str))
			exit(EXIT_FAILURE);
		if (get_cmd_line(str, &cmd_line))
			exit_free_cmdline(&cmd_line);
		if (tokenizer(&cmd_line))
			exit_free_cmdline(&cmd_line);
		//expander(&cmd_line);
		prepare_exec(&cmd_line);
		redirector(&cmd_line);
		if (!global.redir_error)
			exec(cmd_line);
		free(str); //TODO: gestionar la liberación final
		free_all(&cmd_line);
	}
	return (0);
}
