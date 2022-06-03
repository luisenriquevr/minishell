/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:59:03 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/03 20:04:41 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	throw_error(const char *error)
{
	perror(error);
	return (1);
}

int	errcode_print_return(int code, char *msg)
{
	g_global.exit_status = code;
	printf("%s", msg);
	return (code);
}

int	throw_error_exit_status(const char *error, int error_code, int ret)
{
	perror(error);
	g_global.exit_status = error_code;
	return (ret);
}
