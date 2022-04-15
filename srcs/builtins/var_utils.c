/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:29:35 by lvarela           #+#    #+#             */
/*   Updated: 2022/04/15 16:19:22 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		add_new_var(char *new_var)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = global.env;
	if (copy_env(tmp))
		return ; //TODO devolver error
	array_free(tmp);
	while (global.env[i])
		i++;
	global.env[i] = ft_strdup(new_var);
	global.env[i + 1] = NULL;
}

bool		var_valid_name(char *name)
{
	int i;

	i = 0;
	if (!name)
		return (false);
	while(name[i])
	{
		if ((!ft_isalnum(name[i]) && name[0] != '_')
			|| (!ft_isalnum(name[i]) && name[i] != '-'))
			return (false);
		i++;
	}
	return (true);
}

void		change_var(char *name, char *arg)
{
	int		i;
	char	**aux;

	i = 0;
	aux = global.env;
	while (!ft_strnstr(aux[i], name, ft_strlen(name)) && aux[i])
		i++;
	aux = 0;
	free(global.env[i]);
	global.env[i] = ft_strdup(arg);
}

char		*get_var_name(char *envp)
{
	int		i;
	char	*var_name;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && envp[i] != '=')
		i++;
	var_name = (char *)malloc(sizeof(char) * (i + 1));
	while (envp[i] && envp[i] != '=')
	{
		var_name[i] = envp[i]; // comprobar si funciona bien con el i++ asi
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char		*get_var(char *var)
{
	int		i;
	char	*str;
	char	*var_name;

	i = 0;
	str = NULL;
	var_name = get_var_name(global.env[i]);
	while (global.env[i] && ft_strcmp(var_name, var))
	{
		free(var_name);
		var_name = get_var_name(global.env[++i]);
	}
	if (var_name)
		free(var_name);
	if (global.env[i])
		str = global.env[i] + (ft_strlen(str) + 1);
	else if (!ft_strncmp(var, "?", ft_strlen(var)))
	{
		if (global.exit_status > 255)
			global.exit_status = global.exit_status >> 8;
		return (ft_itoa(global.exit_status));
	}
	else
		return (NULL);
	return (ft_strdup(str));
}

