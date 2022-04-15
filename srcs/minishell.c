/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:36:17 by cmarcu            #+#    #+#             */
<<<<<<< HEAD:srcs/readlinepruebas.c
/*   Updated: 2022/04/14 20:48:26 by lvarela          ###   ########.fr       */
=======
/*   Updated: 2022/04/14 20:47:39 by cristianama      ###   ########.fr       */
>>>>>>> 3885fcfa73415267c786887cf5fc03992d92f761:srcs/minishell.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int copy_env(char **envp)
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
	free(new_envp);
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
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char			*str;
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
		//lstiter_cmd(cmd_line, print_list);
		if (tokenizer(&cmd_line))
			exit_free_cmdline(&cmd_line);
		//lstiter_cmd(cmd_line, print_list);
		//expander(&cmd_line);
		prepare_exec(&cmd_line);
<<<<<<< HEAD:srcs/readlinepruebas.c
		exec(cmd_line);
=======
		exec(&cmd_line, global.env);
>>>>>>> 3885fcfa73415267c786887cf5fc03992d92f761:srcs/minishell.c
		free(str); //TODO: gestionar la liberación final
	}
	return (0);
}
