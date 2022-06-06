/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:36:17 by cmarcu            #+#    #+#             */
/*   Updated: 2022/06/06 16:58:24 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct s_global		g_global;

void	init_export(void)
{
	int		i;
	int		j;
	char	abc;

	i = 0;
	j = 0;
	abc = 'A';
	g_global.export = (char **)calloc(g_global.env_len, sizeof(char *));
	while (i < g_global.env_len)
	{
		j = -1;
		while (g_global.env[++j])
		{
			if (g_global.env[j][0] == abc)
				g_global.export[i++] = put_quotes(g_global.env[j]);
		}
		if (++abc == '`')
			break ;
		else if (abc == '[')
			abc = 'a';
		else if (abc == '{')
			abc = '_';
	}
}
/*
int	set_min_env(void)
{
	char	**min_env;
	char	*pwd;
	char	*shlvl;

	pwd = getcwd(NULL, 0);
	shlvl = ft_itoa(g_global.shlvl);
	min_env = (char **)malloc(sizeof(char *) * 4);
	min_env[0] = ft_strjoin("PWD=", pwd);
	free(pwd);
	min_env[1] = ft_strjoin("SHLVL=", shlvl);
	free(shlvl);
	min_env[2] = ft_strdup("_=/usr/bin/env");	
	min_env[3] = NULL;
	g_global.env = min_env;
	return (0);
}
*/
int	init_env(char **envp)
{
	char	**new_envp;
	int		i;
	char	*shlvl;

	if (!envp)
		return (1);
	//if (envp == NULL && g_global.env == NULL)
	//	return (set_min_env());
	new_envp = (char **)calloc(g_global.env_len, sizeof(char *));
	if (!new_envp)
		return (errcode_print_return(50, "Malloc error"));
	i = 0;
	shlvl = ft_itoa(g_global.shlvl);
	while (envp[i])
	{
		if (!ft_strncmp("SHLVL=\n", envp[i], 6))
			new_envp[i] = ft_strjoin("SHLVL=", shlvl);
		else
			new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	free(shlvl);
	new_envp[i] = NULL;
	g_global.env = new_envp;
	return (0);
}

int	init_global(char **env)
{
	g_global.exit_status = 0;
	g_global.env_len = array_length(env) + 1;
	if (env)
		g_global.shlvl = get_shlvl(env);
	if (g_global.shlvl < 0)
		g_global.shlvl = 0;
	g_global.shlvl += 1;
	init_env(env);
	init_export();
	g_global.fd_stdin = dup(STDIN_FILENO);
	g_global.fd_stdout = dup(STDOUT_FILENO);
	g_global.nheredoc = 0;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char		*str;
	t_cmd_line	*cmd_line;

	cmd_line = NULL;
	check_args_init(argc, argv, env);
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		str = readline("minishell $ ");
		if (str && *str)
			add_history(str);
		if (parser(str, &cmd_line))
			exec(cmd_line);
		free(str);
		free_all(&cmd_line);
	}
	close(g_global.fd_stdin);
	close(g_global.fd_stdout);
	exit (0);
}
