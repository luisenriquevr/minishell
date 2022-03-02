/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:40:56 by cristianama       #+#    #+#             */
/*   Updated: 2022/03/02 20:41:48 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

extern int exit_status;

void set_file(t_type previous_token, t_token *token)
{
	t_type type;

	type = token->type;
	if (previous_token == HERE_DOC)
		token->type = LIMITOR;
	else if (previous_token == D_GREATER)
		token->type = OUT_FILE_APPEND;
	else if (previous_token == LESS)
		token->type = IN_FILE;
	else if (previous_token == GREATER)
		token->type = OUT_FILE;
}
bool is_file(t_type type)
{
	if (type == OUT_FILE_APPEND || type == OUT_FILE
		|| type == IN_FILE || type == HERE_DOC)
		return (true);
	return (false);
}

bool set_limitor(t_token **current_token)
{
	t_token *t;
	bool limitor_flag;

	t = *current_token;
	limitor_flag = false;
	while (t)
	{
		if (t->type == HERE_DOC)
			limitor_flag = true;
		else if (limitor_flag && t->str && t->str[0])
		{
			if (is_file(t->type))
				break;
			t->type = LIMITOR;
			limitor_flag = false;
		}
		t = t->next;
	}
	return (limitor_flag);
}

bool set_file_type(t_token **current_token)
{
	t_token *t;
	bool file_flag;
	t_type prev_type;

	t = *current_token;
	file_flag = false;
	while (t)
	{
		if (file_flag && is_file(t->type))
			exit_status = 42; //Arreglar aquí
		else if (is_file(t->type))
		{
			prev_type = t->type;
			file_flag = true;
		}
		else if (file_flag && t->str && t->str[0])
		{
			set_file(prev_type, &t);
			file_flag = false;
		}
		t = t->next;
	}
	return (file_flag); //Arreglar aquí
}