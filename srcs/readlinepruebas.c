/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlinepruebas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:36:17 by cmarcu            #+#    #+#             */
/*   Updated: 2022/02/19 19:16:45 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int exit_status; //Variable global

void check_quotes(char *str)
{
	t_quote quote;
	int i;

	quote = NONE;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (quote == NONE)
				quote = DOUBLE;
			else if (quote == DOUBLE)
				quote = NONE;
		}
		if (str[i] == '\'')
		{
			if (quote == NONE)
				quote = SINGLE;
			else if (quote == SINGLE)
				quote = NONE;
		}
		i++;
	}
	if (quote != NONE)
		exit_status = 14;
}

void check_str(char *str)
{
	int		i;
	bool	after_pipe; //No sé si podemos usar esta librería

	i = 0;
	after_pipe = false;
	if (str == NULL)
		exit_status = 10; //Probablemente esto acabe siendo una función que libere todo lo que hayamos alojado y pase el exit_status como parámetro
	while (str[i])
	{
		// "     cat    |  echo | blah |"
		while (str[i] == ' ')
			i++;
		if (str[i] == '|')
		{
			if (!after_pipe)
				exit_status = 12; //tendremos que ponernos de acuerdo para un conjunto de estados de error :)
			after_pipe = true;
		}
		i++;
	}
	check_quotes(str);
}

int get_cmd_line(char *str, t_cmd_line **cmd_line)
{
	t_cmd_line	*new;

	if (str != NULL && *cmd_line != NULL)
	{
		new = malloc(sizeof(t_cmd_line));
		if (new == NULL)
			return (-1);
		new->str = NULL;
		new->next = NULL;
		//Tengo que recorrer str en busca de | (comprobando que no esté dentro
		//de comillas), y guardar el índice de inicio y final del trozo de string
		//que esté antes del pipe y hacer un malloc de eso y un strncpy de eso
		//en el str de la estructura de command_line.
		//posicion_actual_string es el índice del string en el que hemos encontrado un pipe
		//inicio_comando es el índice del string en el que empieza el comando
		// hola | quease
		// ^    ^
		//inicio_comando es el primer gorrito y posicion_actual_comando es el segundo
		new->str = malloc(sizeof(char) * (posicion_actual_string - inicio_comando + 1));
		//Comprobar el fallo del malloc
		new->str = ft_strncpy(new->string, str + inicio_comando, posicion_actual_string - inicio_comando);
		//Con una de las funciones de listas añadir al final de cmd_line el puntero a new como next
		ft_lstadd_back(*cmd_line, new);
	}
}

int main(int argc, char **argv, char **env)
{
	char			*str;
	t_cmd_line	*cmd_line;

	cmd_line = NULL;
	exit_status = 0;
	while (1)
	{
		str = readline("minishell $ ");
		add_history(str); //Esto añade la historia de comandos, hace que funcione la flecha para arriba
		check_str(str);
		get_cmd_line(str, &cmd_line);
		free(str);
	}
}

/*
* Desde el main, después de comprobar que el str de readline no es null y de chequear el str para
* que el primer carácter distinto de espacio no sea un pipe y que las comillas estén cerradas
*
*
*
*
*
*
*/
