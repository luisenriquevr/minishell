/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:31:32 by cristianama       #+#    #+#             */
/*   Updated: 2022/05/14 06:56:43 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
* Esta funcion mide la longitud del comando que hay guardado en el token
* y asigna al token el tipo que corresponda en funcion de la longitud.
* Si no es ninguno de los tipos pero mide mas de cero se le asigna el tipo ARG.
* Duda: si el str fuera >>> se le asignaria el tipo ARG, eso se gestiona despues
* en la ejecucion o deberia dar fallo aqui? (Si no pongo tildes es por el teclado en ingles juasjuas)
*/
void	set_token_type(t_token *t)
{
	size_t	length;

	length = t->str != NULL ? ft_strlen(t->str) : 0;
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

/*
* Crear una estructura de t_token
* Inicializar la estructura con todo a null
* Copiar con ft_strncpy en str del nuevo t_token
* Chequear el tipo de lo que haya en token->str y poner token->type
* Añadir el token relleno al final de la lista de token dentro del comando
*/
int	fill_token_list(t_cmd_line **cmd, char *str, int curr_pos, int cmd_start)
{
	t_token	*token;

	token = malloc(sizeof(t_token)); //TODO: liberar en gestión de errores
	if (!token) //en vez de if (token == NULL) ?
		return (errcode_print_return(50, "Malloc error"));
	token->str = NULL;
	token->type = EMPTY;
	token->exp = false;
	token->quote = NONE;
	token->next = NULL;
	token->str = malloc(sizeof(char *) * (curr_pos - cmd_start + 1)); //TODO: liberar en gestión de errores
	if (!token->str) //en vez de if (token == NULL) ?
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
		while ((*cmd)->str[curr_pos] == ' ') //Sustituir por ft_isspace?
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

	current_cmd = *cmd_line; /* *cmd_line representa el primer nodo*/
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
			return (errcode_print_return(12, "minishell: syntax error\n"));
		if (set_file_type(current_cmd))
			return (errcode_print_return(12, "minishell: syntax error\n"));
		current_cmd = current_cmd->next;
	}
	return (0);
}
