/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:23:05 by cmarcu            #+#    #+#             */
/*   Updated: 2022/03/02 20:42:47 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

/*
* Hay que declarar todas las listas antes de definirlas para que el *next pueda
* ser del tipo de la lista
*/
typedef struct s_cmd_line t_cmd_line;
typedef struct s_token t_token;
typedef enum quote t_quote;
typedef enum type t_type;

enum quote
{
	NONE,
	SINGLE,
	DOUBLE,
	END
};

enum type
{
	EMPTY,
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
};

struct s_cmd_line
{
	char 		*str;
	t_token		*head_token;
	t_cmd_line	*next;
};

struct s_token
{
	char *str;
	t_type type;
	bool exp;
	t_token *next;
};

/* -------------------------------PARSEO------------------------------- */

/*FUNCIONES DE CHEQUEOS VARIOS*/
void	check_str(char *str);
void	check_quotes(char *str);
void	check_redirection(char *str, int *i);
void	check_arg(char *s, int *i);
bool	check_builtin(char *arg);

/*RELLENAR LA LISTA DE COMANDOS*/
void	get_cmd_line(char *str, t_cmd_line **cmd_line);
void	fill_cmd_list(t_cmd_line **cmd_line, char *str, int end, int start);
void	look_for_pipe(char *str, int *current_position);
void	lstadd_back_cmd(t_cmd_line **lst, t_cmd_line *new);
void	lstiter_cmd(t_cmd_line *lst, void (*f)(char *));
void	print_list(char *str);

/*TOKENIZAR LA LISTA DE COMANDOS*/
void	tokenizer(t_cmd_line **cmd_line);
void	tokenize_cmd(t_cmd_line **cmd);
void	fill_token_list(t_cmd_line **cmd, char *str, int curr_pos, int cmd_start);
void	set_token_type(t_token *t);
void	lstadd_back_token(t_token **lst, t_token *new);
bool	set_file_type(t_token **current_token);
bool	set_limitor(t_token **current_token);
bool	is_file(t_type type);
void	set_file(t_type previous_token, t_token *token);

/*EXPANDIR LA LISTA DE COMANDOS*/

/* -----------------------------EJECUCIÓN------------------------------ */

#endif
