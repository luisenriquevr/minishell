/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:10:02 by lvarela           #+#    #+#             */
/*   Updated: 2022/04/13 17:24:03 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			var_export(char *var)
{
	char	*var_new;
	char	*var_name;

	var_name = get_var_name(var);
	if (!var_valid_name(var_name))
	{
		if (var_name)
			free(var_name);
		return (throw_error_exit_status("Export not a valid identifier", 1, -1));
	}
	var_new = get_var_name(var_name);
	if (ft_strchr(var, '=') && !var_new)
		add_new_var(var);
	else if (ft_strchr(var, '=') && var_new)
		change_var(var_name, var);
	if (var_name)
		free (var_name);
	if (var_new)
		free (var_new);
	return (0);
}

void		print_export(void)
{
	int		i;
	
	i = 0;
	while (global.env_export[i])
		printf("%s\n", global.env_export[i++]);
}

int			builtin_export(char **cmd)
{
	int		i;

	i = 1;
	if (array_length(cmd) == 1)
		print_export();
	while (cmd[i])
	{
		if (cmd[i])
		{
			if (var_export(cmd[i]))
				return(1);
		}
		i++;
	}
	if (global.env_export)
	{
		array_free(global.env_export);
		//global.env_export = create_export();
		// hay que crear una funcion que cree export
	}
	return (1);
}