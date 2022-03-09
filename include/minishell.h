/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:23:05 by cmarcu            #+#    #+#             */
/*   Updated: 2022/03/07 16:42:47 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# define READ_END	0
# define WRITE_END	1

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
	char		**to_exec;
	t_token		*head_token;
	t_cmd_line	*next;
};

struct s_token
{
	char *str;
	t_type type;
	bool exp;
	t_quote quote;
	t_token *next;
};

struct s_global
{
	int		exit_status;
	char	**env;
	char	**env_export; //Para qué
	int		env_len;
	int		fd_stdin;
	int		fd_stdout;
	int		signal_status;
} global;

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
bool	set_file_type(t_cmd_line *current_token);
bool	set_limitor(t_cmd_line *current_token);
bool	is_file(t_type type);
void	set_file(t_type previous_token, t_token *token);

/*EXPANDIR LA LISTA DE COMANDOS*/
void	expander(t_cmd_line **cmd_line);
void	expand_token(t_token *token);
t_quote	close_quote(t_quote open, t_quote close, int *i);
void	expand_word(t_token *token, t_quote quote, char *str, int *i);
void	check_and_expand_env(t_token *t, char *str, char *dest, int *i);
void	expand_no_env(char *str, char *dest, int *i);
void	expand_word_single_quote(char *str, char *dest, int *i);
void	expand_env(t_token *t, char *str, char *dest, int *i);

/* -----------------------------EJECUCIÓN------------------------------ */
int		exec(t_cmd_line *cmd, char **envp);
int		builtin_checker(char *cmd);
int		access_checker(char **cmd_to_exec, char **envp);

/* -------------------------GESTIÓN DE ERRORES------------------------- */
int		print_error(const char *error);

/* ------------------------------VARIOS-------------------------------- */
void	printtitle();
t_quote	update_quotes(char c, t_quote quote);
#endif
