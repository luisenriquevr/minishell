/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:31:32 by cristianama       #+#    #+#             */
/*   Updated: 2022/02/27 00:40:21 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

extern int exit_status;
/*
* Esta funcion mide la longitud del comando que hay guardado en el token
* y asigna al token el tipo que corresponda en funcion de la longitud.
* Si no es ninguno de los tipos pero mide mas de cero se le asigna el tipo ARG.
* Duda: si el str fuera >>> se le asignaria el tipo ARG, eso se gestiona despues
* en la ejecucion o deberia dar fallo aqui? (Si no pongo tildes es por el teclado en ingles juasjuas)
*/
void set_token_type(t_token *t)
{
	size_t length;

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

void fill_token_list(t_cmd_line **cmd, char *str, int curr_pos, int cmd_start)
{
	/*
	* Crear una estructura de t_token
	* Inicializar la estructura con todo a null
	* Copiar con ft_strncpy en str del nuevo t_token
	* Chequear el tipo de lo que haya en token->str y poner token->type
	* Añadir el token relleno al final de la lista de token dentro del comando
	*/

	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token) //en vez de if (token == NULL) ?
		exit_status = 4;
	token->str = NULL;
	token->type = EMPTY;
	token->exp = false;
	token->next = NULL;
	token->str = malloc(sizeof(char *) * (curr_pos - cmd_start + 1));
	if (!token->str) //en vez de if (token == NULL) ?
		exit_status = 4;
	token->str = ft_strncpy(token->str, str + cmd_start, curr_pos - cmd_start);
	set_token_type(token);
	lstadd_back_token(&(*cmd)->head_token, token);
}

void tokenize_cmd(t_cmd_line **cmd)
{
	int curr_pos;
	int cmd_start;

	curr_pos = 0;
	cmd_start = 0;
	while ((*cmd)->str[curr_pos])
	{
		while ((*cmd)->str[curr_pos] == ' ') //Sustituir por ft_ispace?
			curr_pos++;
		cmd_start = curr_pos;
		if ((*cmd)->str[curr_pos] && ((*cmd)->str[curr_pos] == '<' 
		|| (*cmd)->str[curr_pos] == '>'))
			check_redirection((*cmd)->str, &curr_pos);
		else
			check_arg((*cmd)->str, &curr_pos);
		fill_token_list(cmd, (*cmd)->str, curr_pos, cmd_start);
	}
}

void tokenizer(t_cmd_line **cmd_line)
{
	t_cmd_line *current_node;

	current_node = *cmd_line; /* *cmd_line representa el primer nodo*/
	while (current_node)
	{
		tokenize_cmd(&current_node);
		current_node = current_node->next;
	}
}