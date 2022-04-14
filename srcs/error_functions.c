/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:36:08 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/14 19:12:55 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	print_error(const char *error)
{
	perror(error);
	return (1);

int	exit_free_cmdline(t_cmd_line **cmd_line)
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
			if ((*cmd_line)->to_exec)
				free((*cmd_line)->to_exec);
			if ((*cmd_line)->head_token)
				free_token(cmd_line);
			free((*cmd_line));
			*cmd_line = tmp;
		}
	}
	return (1);
}