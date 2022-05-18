/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:48:58 by cristianama       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/18 15:55:27 by lvarela          ###   ########.fr       */
=======
/*   Updated: 2022/05/14 06:58:10 by cmarcu           ###   ########.fr       */
>>>>>>> 2df3d589d24949d1ef2d7da83da4d3473ea85988
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
