/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:48:58 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/11 21:04:16 by cristianama      ###   ########.fr       */
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
