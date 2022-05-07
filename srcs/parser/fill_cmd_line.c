/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:26:32 by cristianama       #+#    #+#             */
/*   Updated: 2022/05/07 18:30:53 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
* Esta función recorre el string que le llega hasta que encuentra un pipe
* Si el pipe está dentro de comillas, lo ignora. Refactorizar el actualizado
* del estado de las comillas porque ya se ha repetido ese código dos veces.
* La función avanza sobre el puntero del str hasta la posición del pipe.
*/

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

/*
* Esta función recibe la línea de comandos y un índice de comienzo y final
* para copiar al final de la lista de cmd_line el trozo de string comprendido
* entre inicio y final. Si algo aquí dentro fallara tenemos que controlar el
* error, liberar y salir.
*/
int	fill_cmd_list(t_cmd_line **cmd_line, char *str, int end, int start)
{
	t_cmd_line	*new;

	new = malloc(sizeof(t_cmd_line)); //TODO: liberar en gestión de errores
	if (new == NULL)
		return (errcode_print_return(50, "Malloc error")); //TODO: gestionar error
	new->str = NULL;
	new->head_token = NULL;
	new->next = NULL;
	new->exec = true;
	new->to_exec = NULL;
	new->fd_in = 0;
	new->fd_out = 0;
	new->str = malloc(sizeof(char) * (end - start + 1)); //TODO: liberar en gestión de errores
	if (new->str == NULL)
		return (errcode_print_return(50, "Malloc error")); //TODO: gestionar error
	new->str = ft_strncpy(new->str, str + start, end - start);
	lstadd_back_cmd(cmd_line, new);
	return (0);
}

/*
* Esta función avanza el puntero del string de command line hasta la posición
* un pipe válido (que no esté entre comillas) y llama a la función que rellena
* la lista con los índices de comienzo y final del comando bien calculados.
*/
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
			// hola | adios
			look_for_pipe(str, &curr_pos);
			if (fill_cmd_list(cmd_line, str, curr_pos, cmd_start))
				return (1);
			cmd_start = curr_pos;
			cmd_start++;
			if (str[curr_pos])
				curr_pos++;
			printf("%d\n", curr_pos);

		}
	}
	return (0);
}
