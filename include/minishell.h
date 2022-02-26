/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:23:05 by cmarcu            #+#    #+#             */
/*   Updated: 2022/02/26 13:05:55 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <stdbool.h>

/*
* Hay que declarar todas las listas antes de definirlas para que el *next pueda
* ser del tipo de la lista
*/
typedef struct s_cmd_line t_cmd_line;
typedef struct s_token t_token;

struct s_cmd_line
{
	char 		*str;
	t_cmd_line	*next;
};

struct s_token
{
	char *str;
	t_type type;
	bool exp;
	t_token *next;
};

typedef enum quote
{
	NONE,
	SINGLE,
	DOUBLE,
	END
}	t_quote;

typedef enum token_type
{
	NONE,
	ARG,
	BUILTIN,
	LESS, //<
	HERE_DOC, //<<
	LIMITOR,//Palabra después de <<
	GREATER, //>
	D_GREATER, //>>
	OUT_FILE_APPEND, //Palabra después de >>
	OUT_FILE, //Palabra después de >
	IN_FILE //Palabra después de <
}	t_type;

/* -------------------------------PARSEO------------------------------- */

/*FUNCIONES DE CHEQUEOS VARIOS*/
void	check_str(char *str);
void	check_quotes(char *str);
void	check_redirection(char *str, int *i);
void	check_arg(char *s, int *i);

/*RELLENAR LA LISTA DE COMANDOS*/
void	get_cmd_line(char *str, t_cmd_line **cmd_line);
void	fill_cmd_list(t_cmd_line **cmd_line, char *str, int end, int start);
void	look_for_pipe(char *str, int *current_position);
void	ft_lstadd_back(t_cmd_line **lst, t_cmd_line *new);
t_cmd_line	*ft_lstlast(t_cmd_line *lst);
void	print_list(char *str);

/*TOKENIZAR LA LISTA DE COMANDOS*/
void	tokenizer(t_cmd_line **cmd_line);
void	tokenize_cmd(t_cmd_line **cmd);
void	fill_token_list(t_cmd_line **cmd, char *str, int curr_pos, int cmd_start);
void	set_token_type(t_token *t);

/*EXPANDIR LA LISTA DE COMANDOS*/

/* -----------------------------EJECUCIÓN------------------------------ */

#endif
