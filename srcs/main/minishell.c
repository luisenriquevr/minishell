/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:36:17 by cmarcu            #+#    #+#             */
/*   Updated: 2022/06/03 21:07:19 by cmarcu           ###   ########.fr       */
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

int	init_env(char **envp)
{
	char	**new_envp;
	int		i;

	if (!envp)
		return (1);
	new_envp = (char **)calloc(g_global.env_len, sizeof(char *));
	if (!new_envp)
		return (errcode_print_return(50, "Malloc error"));
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("SHLVL=\n", envp[i], 6))
			new_envp[i] = ft_strjoin("SHLVL=", ft_itoa(g_global.shlvl));
		else
			new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	g_global.env = new_envp;
	return (0);
}

int	init_global(char **env)
{
	if (!g_global.shlvl)
		g_global.shlvl = 1;
	g_global.shlvl += 1;
	g_global.exit_status = 0;
	g_global.env_len = array_length(env) + 1;
	if (init_env(env))
		return (50);
	init_export();
	g_global.fd_stdin = dup(STDIN_FILENO);
	g_global.fd_stdout = dup(STDOUT_FILENO);
	g_global.signal_status = 0;
	g_global.from_heredoc = true;
	return (0);
}

void	parser(char *str, t_cmd_line **cmd_line)
{
	if (check_str(str))
		str = clear_line(str);
	if (get_cmd_line(str, cmd_line))
		exit_free_cmdline(cmd_line);
	if (tokenizer(cmd_line))
		exit_free_cmdline(cmd_line);
	expander(cmd_line);
	prepare_exec(cmd_line);
	redirector(cmd_line);
}

int	main(int argc, char **argv, char **env)
{
	char		*str;
	t_cmd_line	*cmd_line;

	cmd_line = NULL;
	check_args_init(argc, argv, env);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		if (g_global.from_heredoc)
			str = readline("minishell $ ");
		else
			str = readline(NULL);
		g_global.from_heredoc = true;
		if (str && *str)
			add_history(str);
		parser(str, &cmd_line);
		if (g_global.from_heredoc)
			exec(cmd_line);
		free(str);
		free_all(&cmd_line);
	}
	close(g_global.fd_stdin);
	close(g_global.fd_stdout);
	exit (0);
}
