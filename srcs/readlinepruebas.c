/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlinepruebas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:36:17 by cmarcu            #+#    #+#             */
/*   Updated: 2022/03/06 14:08:50 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	**copy_env(char **envp)
{
	char	**new_envp;
	int		i;

	new_envp = (char **)malloc(sizeof(char *) * global.env_len);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	init_global(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	global.exit_status = 0;
	global.env_len = (i + 2);
	global.env = copy_env(env);
	global.env_export = NULL; //create_env_export(); Hasta que lo necesitemos
	global.fd_stdin = dup(STDIN_FILENO);
	global.fd_stdout = dup(STDOUT_FILENO);
	global.signal_status = 0;
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
	init_global(env);
	printtitle();
	while (1)
	{
		str = readline("minishell $ ");
		add_history(str); //Esto añade la historia de comandos, hace que funcione la flecha para arriba
		check_str(str);
		get_cmd_line(str, &cmd_line);
		//lstiter_cmd(cmd_line, print_list);
		tokenizer(&cmd_line);
		lstiter_cmd(cmd_line, print_list);
		//expander(&cmd_line);
		/*Aquí iría a continuación:
		*	Builtins
		*	Redirecciones
		*	Ejecución
		*/
		free(str);
	}
	return (0);
}
