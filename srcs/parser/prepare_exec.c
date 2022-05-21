/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:32:14 by cristianama       #+#    #+#             */
/*   Updated: 2022/05/21 14:18:36 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_cmd_line *cmd)
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
	char		**cmd_to_exec;
	t_token		*t;
	int			i;

	cmd = *cmd_line;
	while (cmd)
	{
		cmd_to_exec = malloc(sizeof(char *) * (count_args(cmd) + 1));
		if (cmd_to_exec == NULL)
			return (errcode_print_return(50, "Malloc error"));
		cmd->to_exec = cmd_to_exec;
		t = cmd->head_token;
		i = -1;
		while (t)
		{
			if (t->type == BUILTIN || t->type == ARG)
				cmd->to_exec[++i] = ft_strdup(t->str);
			t = t->next;
		}
		cmd->to_exec[++i] = NULL;
		cmd = cmd->next;
	}
	return (0);
}
