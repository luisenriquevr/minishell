/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:48:58 by cristianama       #+#    #+#             */
/*   Updated: 2022/05/18 17:15:23 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	free_token(t_cmd_line **cmd_line)
{
	t_token	*temp;

	while ((*cmd_line)->head_token)
	{
		temp = (*cmd_line)->head_token->next;
		if ((*cmd_line)->head_token->str)
			free((*cmd_line)->head_token->str);
		free((*cmd_line)->head_token);
		(*cmd_line)->head_token = temp;
	}
}

int	free_all(t_cmd_line **cmd_line)
{
	t_cmd_line	*aux;

	if (cmd_line)
	{
		while (*cmd_line)
		{
			aux = (*cmd_line)->next;
			if ((*cmd_line)->str)
				free((*cmd_line)->str);
			if ((*cmd_line)->to_exec)
				array_free((*cmd_line)->to_exec);
			if ((*cmd_line)->head_token)
				free_token(cmd_line);
			free((*cmd_line));
			*cmd_line = aux;
		}
	}
	return (1);
}

int	exit_free_cmdline(t_cmd_line **cmd_line)
{
	if (free_all(cmd_line))
		return (25);
	return (0);
}
