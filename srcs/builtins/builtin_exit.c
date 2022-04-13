/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:21:51 by lvarela           #+#    #+#             */
/*   Updated: 2022/04/13 17:29:14 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			builtin_exit(char **cmd)
{
	if (array_length(cmd) > 2)
		return (throw_error_exit_status("Error: Too many arguments", 1, 1));
	printf("exit\n");

}