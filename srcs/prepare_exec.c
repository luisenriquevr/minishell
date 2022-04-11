/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:32:14 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/11 19:40:10 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_args(t_cmd_line *cmd)
{
	t_token		*t;
	int			arg_length;

	t = cmd->head_token;
	arg_length = 0;
	while (t)
	{
		if (t->type == BUILTIN || t->type == ARG)
			arg_length++;
		t = t->next;
	}
	return (arg_length);
}

int	prepare_exec(t_cmd_line **cmd_line)
{
	t_cmd_line	*cmd;
	char		**to_exec;
	t_token		*t;
	int			i;

	cmd = *cmd_line;
	while (cmd)
	{
		to_exec = malloc(sizeof(char *) * (count_args(cmd) + 1)); //TODO: liberar en gestión de errores
		if (to_exec == NULL)
			return (errcode_print_return(50, "Malloc error"));
		cmd->argv = to_exec;
		t = cmd->head_token;
		i = -1;
		while (t)
		{
			if (t->type == BUILTIN || t->type == ARG)
				cmd->argv[i++] = t->str;
			t = t->next;
		}
		cmd->argv[i] = NULL;
		cmd = cmd->next;
	}
	return (0);
}