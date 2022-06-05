/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:59:03 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/05 18:25:56 by lvarela          ###   ########.fr       */
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
	ft_putendl_fd(msg, 2);
	return (code);
}

int	throw_error_exit_status(char *error, int error_code, int ret)
{
	ft_putendl_fd(error, 2);
	g_global.exit_status = error_code;
	return (ret);
}
