/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:08:03 by lvarela           #+#    #+#             */
/*   Updated: 2022/04/23 16:36:35 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		unset(char *cmd, char **env)
{
	int		i;
	char	*old_var;
	char	*var_name;

	i = 0;
	var_name = get_var(env[i]); // no se si tiene que estar protegido, creo que no
	while (env[i] && ft_strcmp(var_name, cmd))
	{
		free(var_name);
		var_name = get_var(env[++i]);
	}
	if (var_name)
		free(var_name);
	if (env[i])
	{
		old_var = env[i]; // tengo mis dudas y creo que se puede hacer sin old_var
		while (env[i])
		{
			env[i] = env[i + 1];
			i++;
		}
		free(old_var);
		global.env_len -= 1;
	}
}

int			builtin_unset(char **cmd)
{
	int		i;
	char	**tmp;
	
	i = 0;
	tmp = global.env;
	while (cmd[i])
	{
		if (cmd[i])
			unset(cmd[i], tmp);
		i++;
	}
	if (global.export)
	{
		array_free(global.export);
		//global.export = create_export();
		// necesitamos una funcion que nos cree export
	}
	return (1);
}