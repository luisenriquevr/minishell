/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlinepruebas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:36:17 by cmarcu            #+#    #+#             */
/*   Updated: 2022/02/26 22:31:00 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int exit_status; //Variable global

int main(void) //int argc, char **argv, char **env
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
		lstiter_cmd(cmd_line, print_list);
		/*Aquí iría a continuación:
		*	Tokenizer
		*	Expander
		*	Builtins
		*	Redirecciones
		*	Ejecución
		*/
		tokenizer(&cmd_line);
		lstiter_cmd(cmd_line, print_list);
		free(str);
	}
	return (0);
}
