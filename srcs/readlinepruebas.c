/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlinepruebas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:36:17 by cmarcu            #+#    #+#             */
/*   Updated: 2022/02/18 20:13:12 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include "../includes/minishell.h"

int get_cmd_line(char *str, t_command_line **cmd_line)
{
	t_command_line	*new;

	if (str != NULL && *cmd_line != NULL)
	{
		new = malloc(sizeof(t_command_line));
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
		new->str = malloc(sieof(char) * (posicion_actual_string - inicio_comando + 1));
		//Comprobar el fallo del malloc
		new->str = ft_strncpy(new->string, str + inicio_comando, posicion_actual_string - inicio_comando);
		//Con una de las funciones de listas añadir al final de cmd_line el puntero a new como next
		ft_lstadd_back(*cmd_line, new);
	}
}

int main(void)
{
	char			*str;
	t_command_line	*cmd_line;

	cmd_line = NULL;
	while (1)
	{
		str = readline("minishell $ ");
		add_history(str); //Esto añade la historia de comandos, hace que funcione la flecha para arriba
		get_cmd_line(str, &cmd_line);
		free(str);
	}
}
