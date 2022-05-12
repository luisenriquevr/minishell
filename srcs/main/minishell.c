/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:36:17 by cmarcu            #+#    #+#             */
/*   Updated: 2022/05/12 18:05:02 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_global		global;

void	init_export(void)
{
	int		i;
	int		j;
	char	abc;

	i = 0;
	j = 0;
	abc = 'A';
	global.export = (char **)calloc(global.env_len, sizeof(char *));
	while (i < global.env_len)
	{
		j = 0;
		while (global.env[j])
		{
			if (global.env[j][0] == abc)
				global.export[i++] = ft_strjoin("declare -x ", global.env[j]);
			j++; // esto quizás se puede sumar en el while y ya no nos pasariamos de lineas
		}
		if (++abc == '`')
			break ;
		else if (abc == '[')
			abc = 'a';
		else if (abc == '{')
			abc = '_';
	}
}

int	init_env(char **envp)
{
	char	**new_envp;
	int		i;

	new_envp = (char **)calloc(global.env_len, sizeof(char *)); //TODO: liberar en gestión de errores
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
	if (init_env(env))
		return (50);
	init_export();
	global.signal_status = 0;
	global.contador = 0;
	return (0);
}

void	printtitle(void)
{
	printf("                 _       _     _          _ _ 	\n");
	printf("                (_)     (_)   | |        | | |	\n");
	printf("       _ __ ___  _ _ __  _ ___| |__   ___| | |	\n");
	printf("      | '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |	\n");
	printf("      | | | | | | | | | | \\__ \\ | | |  __/ | |	\n");
	printf("      |_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|	\n");
	printf("----------------------------------------------------\n");
}

int	main(int argc, char **argv, char **env)
{
	char		*str;
	t_cmd_line	*cmd_line;

	cmd_line = NULL;
	if (argc != 1 || !argv)
	{
		throw_error("Invalid arguments: try './minishell'");
		exit(EXIT_FAILURE);
	}
	if (init_global(env))
		exit(EXIT_FAILURE);
	global.fd_stdin = dup(STDIN_FILENO); // -> 1
	global.fd_stdout = dup(STDOUT_FILENO); // -> 0
	//printtitle();
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("minishell $ ");
		if (str && *str)
			add_history(str);
		if (check_str(str))
			exit(EXIT_FAILURE);
		if (get_cmd_line(str, &cmd_line))
			exit_free_cmdline(&cmd_line);
		if (tokenizer(&cmd_line))
			exit_free_cmdline(&cmd_line);
		expander(&cmd_line);
		prepare_exec(&cmd_line);
		//system("lsof -c minishell");
		redirector(&cmd_line);
		exec(cmd_line);
		free(str); //TODO: gestionar en la liberación final
		free_all(&cmd_line);
	}
	close(global.fd_stdin);
	close(global.fd_stdout);
	return (0);
}
