/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:31:32 by cristianama       #+#    #+#             */
/*   Updated: 2022/06/05 19:13:39 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	set_token_type(t_token *t)
{
	size_t	length;

	if (t->str == NULL)
		length = 0;
	else
		length = ft_strlen(t->str);
	if (length == 1)
	{
		if (t->str[0] == '<')
			t->type = LESS;
		else if (t->str[0] == '>')
			t->type = GREATER;
	}
	if (length == 2)
	{
		if (t->str[0] == '<' && t->str[1] == '<')
			t->type = HERE_DOC;
		else if (t->str[0] == '>' && t->str[1] == '>')
			t->type = D_GREATER;
	}
	if (check_builtin(t->str))
		t->type = BUILTIN;
	if (length != 0 && t->type == EMPTY)
		t->type = ARG;
}

void	set_quote(t_token *t)
{
	t_quote	quote;
	int		i;
	char	*str;

	quote = NONE;
	i = 0;
	str = t->str;
	while (str[i])
	{
		if (str[i] == '"' && quote == NONE)
			quote = DOUBLE;
		else if (str[i] == '\'' && quote == NONE)
			quote = SINGLE;
		i++;
	}
	t->quote = quote;
}

int	fill_token_list(t_cmd_line **cmd, char *str, int curr_pos, int cmd_start)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (errcode_print_return(50, "Malloc error"));
	token->str = NULL;
	token->type = EMPTY;
	token->exp = false;
	token->quote = NONE;
	token->next = NULL;
	token->str = malloc(sizeof(char *) * (curr_pos - cmd_start + 1));
	if (!token->str)
		return (errcode_print_return(50, "Malloc error"));
	token->str = ft_strncpy(token->str, str + cmd_start, curr_pos - cmd_start);
	set_token_type(token);
	set_quote(token);
	lstadd_back_token(&(*cmd)->head_token, token);
	return (0);
}

int	tokenize_cmd(t_cmd_line **cmd)
{
	int	curr_pos;
	int	cmd_start;

	curr_pos = 0;
	cmd_start = 0;
	while ((*cmd)->str[curr_pos])
	{
		while ((*cmd)->str[curr_pos] == ' ' || (*cmd)->str[curr_pos] == '\t')
			curr_pos++;
		cmd_start = curr_pos;
		if ((*cmd)->str[curr_pos] && ((*cmd)->str[curr_pos] == '<'
				|| (*cmd)->str[curr_pos] == '>'))
			check_redirection((*cmd)->str, &curr_pos);
		else
			check_arg((*cmd)->str, &curr_pos);
		if (fill_token_list(cmd, (*cmd)->str, curr_pos, cmd_start))
			return (1);
	}
	return (0);
}

int	tokenizer(t_cmd_line **cmd_line)
{
	t_cmd_line	*current_cmd;

	current_cmd = *cmd_line;
	while (current_cmd)
	{
		if (tokenize_cmd(&current_cmd))
			return (1);
		current_cmd = current_cmd->next;
	}
	current_cmd = *cmd_line;
	while (current_cmd)
	{
		if (set_limitor(current_cmd))
			return (errcode_print_return(12, "minishell: syntax error"));
		if (set_file_type(current_cmd))
			return (errcode_print_return(12, "minishell: syntax error"));
		current_cmd = current_cmd->next;
	}
	return (0);
}
