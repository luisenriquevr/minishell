#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdbool.h>
#include "../libft/libft.h"

/*
* Hay que declarar todas las listas antes de definirlas para que el *next pueda
* ser del tipo de la lista
*/
typedef struct s_cmd_line t_cmd_line;

struct s_cmd_line
{
	char 		*str;
	t_cmd_line	*next;
};

typedef enum quote
{
	NONE,
	SINGLE,
	DOUBLE,
	END
}	t_quote;

#endif



// typedef enum token
// {
// 	NON,
// 	ARG,
// 	BUILTIN,
// 	OPEN_FILE,
// 	HERE_DOC,
// 	LIMITOR,
// 	CREAT_FILE,
// 	WRITE_FILE,
// 	FILE_IN,
// 	FILE_OUT,
// 	FILE_OUT_OVER,
// 	ENDS
// }				t_e_token;

// struct			s_token
// {
// 	char		*str;				==>		TOKEN EN SI
// 	t_e_token	type;				==>		TIPO DE TOKEN
// 	bool		expanded;			==>		POR EJEMPLO SI ES UNA VARIABLE LOCAL (USUARIO)
// 	t_token		*next;				==>		PUNTERO A LA SIGUIENTE ESTRUCTURA TOKEN
// };

// struct				s_commande_line
// {
// 	char			*string;		==>		AQUÍ EL COMANDO PRINCIPAL
// 	t_token			*first_token;	==>		LISTA DE TOCKENS
// 	char			**envp;			==>		VARIABLE DE ENTORNO
// 	char			**argv;			==>		ARGUMENTOS RECOGIDOS AL INICIO
// 	int				fd_in;			==>		WHAT?
// 	int				fd_out;			==>		WHAT?
// 	char			*name_file;		==>		WHAAAAAT?
// 	t_commande_line	*next;			==>		PUNTERO A LA SIGUIENTE ESTRUCTURA COMANDO
// };
