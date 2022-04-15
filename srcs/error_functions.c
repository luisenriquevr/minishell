/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:36:08 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/15 13:50:47 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	print_error(const char *error)
{
	perror(error);
	return (1);
}

int errcode_print_return(int code, char *msg)
{
	global.exit_status = code;
	printf("%s", msg);
	return code;
}