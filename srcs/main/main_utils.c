/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:02:29 by cmarcu            #+#    #+#             */
/*   Updated: 2022/06/05 17:54:11 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	get_shlvl(char **envp)
{
	int		i;
	char	*str;
	char	*var_name;

	i = 0;
	str = 0;
	var_name = get_var_name(envp[i]);
	while (envp[i] && ft_strcmp(var_name, "SHLVL"))
	{
		free(var_name);
		var_name = get_var_name(envp[++i]);
	}
	if (var_name)
		free(var_name);
	if (envp[i])
		return (ft_atoi(&envp[i][6]));
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

char	*clear_line(char *str)
{
	if (str == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	free(str);
	return (ft_strdup(""));
}

void	check_args_init(int argc, char **argv, char **env)
{
	if (argc != 1 || !argv)
	{
		throw_error("Invalid arguments: try './minishell'");
		exit(EXIT_FAILURE);
	}
	if (init_global(env))
		exit(EXIT_FAILURE);
	printtitle();
}
