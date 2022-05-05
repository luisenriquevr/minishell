/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:10:02 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/04 19:26:05 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
**	Mirando como generar el export, creemos que se puede hacer mediante la ejecucion
**	de env | sort. El unico problema es que aun asi debemos guardar una copia de env
**	en global.export para cuando se declaren variables globales... o no?
*/

int			var_export(char *var)
{
	char	*var_new;
	char	*var_name;

	var_name = get_var_name(var);
	if (!var_valid_name(var_name))
	{
		if (var_name)
			free(var_name);
		return (throw_error_exit_status("Export not a valid identifier", 1, -1)); // se me sale aqui al exportar
	}
	var_new = get_var(var_name);
	if (ft_strchr(var, '=') && !var_new)
		add_new_var(var); // IMPORTANTE ==> con export a=2 deberia de entrar aqui al no existir pero entra en el else
	else if (ft_strchr(var, '=') && var_new)
		change_var(var_name, var);
	// Aqui si no hay igual tiene que meterla solo en export
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
	while (global.export[i])
		printf("%s\n", global.export[i++]);
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
	if (global.export)
	{
		array_free(global.export);
		init_export();
	}
	return (1);
}