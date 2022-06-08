/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:29:35 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/08 18:59:28 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_var(char *new_var)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = g_global.env;
	g_global.env_len += 1;
	printf("%p\n", g_global.env);
	init_env(tmp);
	array_free(tmp);
	while (g_global.env[i])
		i++;
	g_global.env[i] = ft_strdup(new_var);
	g_global.env[i + 1] = NULL;
}

bool	var_valid_name(char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (false);
	while (name[i])
	{
		if ((!ft_isalnum(name[i]) && name[i] != '_')
			|| (name[0] != '_' && !ft_isalpha(name[0])))
			return (false);
		i++;
	}
	return (true);
}

void	change_var(char *var_name, char *arg)
{
	int		i;
	char	**aux;

	i = 0;
	aux = g_global.env;
	while (aux[i] && (!ft_strnstr(aux[i], var_name, (size_t)ft_strlen(var_name))
			|| aux[i][ft_strlen(var_name)] != '='))
		i++;
	aux = 0;
	free(g_global.env[i]);
	g_global.env[i] = ft_strdup(arg);
}

char	*get_var_name(char *envp)
{
	int		i;
	char	*var_name;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && envp[i] != '=')
		i++;
	var_name = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (envp[i] && envp[i] != '=')
	{
		var_name[i] = envp[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*get_var(char *var)
{
	int		i;
	char	*str;
	char	*var_name;

	i = 0;
	str = 0;
	var_name = get_var_name(g_global.env[i]);
	while (g_global.env[i] && ft_strcmp(var_name, var))
	{
		free(var_name);
		var_name = get_var_name(g_global.env[++i]);
	}
	if (var_name)
		free(var_name);
	if (g_global.env[i])
		str = g_global.env[i] + (ft_strlen(var) + 1);
	else if (!ft_strncmp(var, "?", 1))
	{
		if (g_global.exit_status > 255)
			g_global.exit_status = g_global.exit_status >> 8;
		return (ft_itoa(g_global.exit_status));
	}
	else
		return (NULL);
	return (ft_strdup(str));
}
