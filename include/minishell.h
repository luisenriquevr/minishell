/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:50:08 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/08 18:49:45 by lvarela          ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/errno.h>
# include "../libft/libft.h"

# define READ_END	0
# define WRITE_END	1

typedef struct s_cmd_line	t_cmd_line;
typedef struct s_token		t_token;
typedef enum e_quote		t_quote;
typedef enum e_type			t_type;
extern struct s_global		g_global;

enum	e_quote
{
	NONE,
	SINGLE,
	DOUBLE,
	END
};

enum	e_type
{
	EMPTY,
	ARG,
	BUILTIN,
	LESS,
	HERE_DOC,
	LIMITOR,
	GREATER,
	D_GREATER,
	OUT_FILE_APPEND,
	OUT_FILE,
	IN_FILE
};

struct	s_token
{
	char	*str;
	t_type	type;
	bool	exp;
	t_quote	quote;
	int		fd_in;
	int		fd_out;
	t_token	*next;
};

struct	s_cmd_line
{
	char		*str;
	char		**to_exec;
	t_token		*head_token;
	bool		exec;
	int			fd_in;
	int			fd_out;
	t_cmd_line	*next;
};

struct s_global
{
	int		shlvl;
	int		exit_status;
	char	**env;
	char	**export;
	int		env_len;
	int		fd_stdin;
	int		fd_stdout;
	int		nheredoc;
} g_global;

/* -------------------------------PARSEO------------------------------- */

int			parser(char *str, t_cmd_line **cmd_line);

/*FUNCIONES DE CHEQUEOS VARIOS*/
int			check_str(char *str);
int			check_quotes(char *str);
void		check_redirection(char *str, int *i);
void		check_arg(char *s, int *i);
bool		check_builtin(char *arg);

/*RELLENAR LA LISTA DE COMANDOS*/
int			get_cmd_line(char *str, t_cmd_line **cmd_line);
int			fill_cmd_list(t_cmd_line **cmd_line, char *str, int end, int start);
void		look_for_pipe(char *str, int *current_position);
void		lstadd_back_cmd(t_cmd_line **lst, t_cmd_line *new);
void		lstiter_cmd(t_cmd_line *lst, void (*f)(void *));
void		print_list(char *str);

/*TOKENIZAR LA LISTA DE COMANDOS*/
int			tokenizer(t_cmd_line **cmd_line);
int			tokenize_cmd(t_cmd_line **cmd);
int			fill_token_list(t_cmd_line **cmd, char *str, \
		int curr_pos, int cmd_start);
void		set_token_type(t_token *t);
void		lstadd_back_token(t_token **lst, t_token *new);
bool		set_file_type(t_cmd_line *current_token);
bool		set_limitor(t_cmd_line *current_token);
bool		is_file(t_type type);
void		set_file(t_type previous_token, t_token *token);

/*EXPANDIR LA LISTA DE COMANDOS*/
void		expander(t_cmd_line **cmd_line);
void		expand_token(t_token *token);
void		trim_quotes(t_token *t);
bool		update_may_expand(char c, bool expand);
bool		may_expand(char c, bool expand);
char		*expand_var(char *str, char *dest);
char		*go_to_var_end(char *str);
char		*go_to_var_end_quotes(char *str, t_quote quote);

/*PREPARAR EJECUCION*/
int			prepare_exec(t_cmd_line **cmd_line);

/* -----------------------------EJECUCI??N------------------------------ */

int			exec(t_cmd_line *cmd_line);
int			exec_simple(t_cmd_line *cmd);
int			exec_pipes(t_cmd_line *cmd);
int			access_checker(char **cmd_to_exec);
void		redirector(t_cmd_line **cmd_line);
int			redir_heredoc(t_token *token, t_cmd_line *cmd, int *fd);

/*BUILTINS*/
int			builtin_checker(char **cmd);
int			builtin_cd(char **arg);
int			builtin_echo(char **arg);
int			builtin_env(char **cmd);
int			builtin_pwd(char **cmd);
int			builtin_unset(char **cmd);
int			builtin_exit(char **cmd);
int			builtin_export(char **cmd);

/*UTILS*/
int			array_length(char **array);
void		array_free(char **array);
void		change_var(char *name, char *arg);
char		*get_var(char *var);
bool		var_valid_name(char *name);
int			init_env(char **envp);
void		init_export(void);
void		add_new_var(char *new_var);
char		*get_var_name(char *envp);
void		dup_and_close(int old, int new);
void		exec_error_exit(char *str1);
void		set_signals(void);

/* -------------------------GESTI??N DE ERRORES------------------------- */
int			print_error(const char *error);
int			errcode_print_return(int code, char *msg);
int			exit_free_cmdline(t_cmd_line **cmd);
int			free_all(t_cmd_line **cmd_line);
void		free_token(t_cmd_line **cmd_line);

/* -------------------------GESTI??N DE SENALES------------------------- */
void		handle_signal(int sig);
int			redirection(t_token *token, t_cmd_line *cmd);

/* ------------------------------VARIOS-------------------------------- */
void		printtitle(void);
t_quote		update_quotes(char c, t_quote quote);
char		*push_char(char *str, char c);
int			throw_error(const char *error);
int			throw_error_exit_status(char *error, int error_code, int ret);
char		*set_shlvl(void);
char		*clear_line(char *str);
void		check_args_init(int argc, char **argv, char **env);
char		*put_quotes(char *str);
int			init_global(char **env);
int			get_shlvl(char **envp);
int			only_space(char *str);

#endif
