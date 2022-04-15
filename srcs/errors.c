/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:59:03 by lvarela           #+#    #+#             */
/*   Updated: 2022/04/15 19:08:24 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		throw_error(const char *error)
{
	perror(error);
	return (1);
}

int		throw_error_exit_status(const char *error, int error_code, int ret)
{
	perror(error);
	global.exit_status = error_code;
	return (ret);
}
