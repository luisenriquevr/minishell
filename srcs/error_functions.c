/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:36:08 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/11 21:06:46 by cristianama      ###   ########.fr       */
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
	global.exit_status = code; //TODO: gestionar error
	//anadir aqui la imrpesion del mesnaje de error?
	printf("%s", msg);
	return code;
}

int	exit_free_cmdline(t_cmd_line **cmd)
{
	t_cmd_line	*tmp;

	printf("exit\n");
	if (cmd_line)
	{
		while (*cmd_line)
		{
			tmp = (*cmd_line)->next;
			if ((*cmd_line)->str)
				free((*cmd_line)->str);
			if ((*cmd_line)->argv)
				free((*cmd_line)->argv);
			if ((*cmd_line)->head_token)
				free_token(cmd_line);
			free((*cmd_line));
			*cmd_line = tmp;
		}
	}
	return (1);
}