/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:51 by lvarela           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/14 19:44:59 by lvarela          ###   ########.fr       */
=======
/*   Updated: 2022/04/14 21:15:51 by cristianama      ###   ########.fr       */
>>>>>>> 3885fcfa73415267c786887cf5fc03992d92f761
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			builtin_exit(char **cmd)
{
	if (array_length(cmd) > 2)
		return (throw_error_exit_status("Error: Too many arguments", 1, 1));
	printf("exit\n");
	if (!ft_isdigit(cmd[1][0])) // cambiar 
	{
		throw_error("Error: Bad expression");
		exit(255);
	}
	if (!cmd[1])
		exit(EXIT_SUCCESS);
	else
		exit(ft_atoi(cmd[1]));
	return (1);
}
