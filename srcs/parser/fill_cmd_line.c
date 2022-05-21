/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:26:32 by cristianama       #+#    #+#             */
/*   Updated: 2022/05/21 14:17:41 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	look_for_pipe(char *str, int *current_position)
{
	t_quote	quote;

	quote = NONE;
	while (str[*current_position])
	{
		if (str[*current_position] == '"')
		{
			if (quote == NONE)
				quote = DOUBLE;
			else if (quote == DOUBLE)
				quote = NONE;
		}
		if (str[*current_position] == '\'')
		{
			if (quote == NONE)
				quote = SINGLE;
			else if (quote == SINGLE)
				quote = NONE;
		}
		if (str[*current_position] == '|' && quote == NONE)
			return ;
		(*current_position)++;
	}
}

int	fill_cmd_list(t_cmd_line **cmd_line, char *str, int end, int start)
{
	t_cmd_line	*new;

	new = malloc(sizeof(t_cmd_line));
	if (new == NULL)
		return (errcode_print_return(50, "Malloc error"));
	new->str = NULL;
	new->head_token = NULL;
	new->next = NULL;
	new->exec = true;
	new->to_exec = NULL;
	new->fd_in = 0;
	new->fd_out = 0;
	new->str = malloc(sizeof(char) * (end - start + 1));
	if (new->str == NULL)
		return (errcode_print_return(50, "Malloc error"));
	new->str = ft_strncpy(new->str, str + start, end - start);
	lstadd_back_cmd(cmd_line, new);
	return (0);
}

int	get_cmd_line(char *str, t_cmd_line **cmd_line)
{
	int	curr_pos;
	int	cmd_start;

	curr_pos = 0;
	cmd_start = 0;
	if (str != NULL)
	{
		while (str[curr_pos])
		{
			look_for_pipe(str, &curr_pos);
			if (fill_cmd_list(cmd_line, str, curr_pos, cmd_start))
				return (1);
			cmd_start = curr_pos;
			cmd_start++;
			if (str[curr_pos])
				curr_pos++;
		}
	}
	return (0);
}
