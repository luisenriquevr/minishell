/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:02:29 by cmarcu            #+#    #+#             */
/*   Updated: 2022/06/03 21:04:04 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*set_shlvl(void)
{
	char			*ptr;
	char			*name;
	unsigned int	i;

	i = -1;
	ptr = (char *)malloc(sizeof(char) * ((sizeof(char) * 8)));
	if (!ptr)
		return (NULL);
	name = "SHLVL=";
	while (name[++i] != '\0')
		ptr[i] = name[i];
	ptr[i++] = g_global.shlvl;
	ptr[i] = '\0';
	return (ptr);
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
		ft_putstr_fd("exit\n", 0);
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
