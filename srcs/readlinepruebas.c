/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlinepruebas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:36:17 by cmarcu            #+#    #+#             */
/*   Updated: 2022/02/25 21:24:52 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

int exit_status; //Variable global

/*
* Esta función recibe por parámetro la línea de comandos y cuando encuentra
* una comilla del tipo que sea setea el tipo de comillas a ese tipo y hasta
* que no vuelve a encontrar una igual no lo cambia.
* Si cuando acaba el tipo de comilla es distinto de NONE significa que alguna
* se ha quedado sin cerrar y tenemos que gestionar el error, liberar lo que
* sea y salir.
*/
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

/*
* Esta función está MAL (líneas 67-69)
*/
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

/*
* Esta función recorre el string que le llega hasta que encuentra un pipe
* Si el pipe está dentro de comillas, lo ignora. Refactorizar el actualizado
* del estado de las comillas porque ya se ha repetido ese código dos veces.
* La función avanza sobre el puntero del str hasta la posición del pipe.
*/

void look_for_pipe(char *str, int *current_position)
{
	t_quote quote;

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
* Pues eso, strncpy. Hay que refactorizar todas estas cositas en nuevos archivos ya.
*/
char	*ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*
* Función de listas pero adaptada a nuestra estructura. No sé si me convence
*/
t_cmd_line	*ft_lstlast(t_cmd_line *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/*
* Función de listas pero adaptada a nuestra estructura. No sé si me convence
*/
void	ft_lstadd_back(t_cmd_line **lst, t_cmd_line *new)
{
	t_cmd_line *last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

/*
* Esta función recibe la línea de comandos y un índice de comienzo y final
* para copiar al final de la lista de cmd_line el trozo de string comprendido
* entre inicio y final. Si algo aquí dentro fallara tenemos que controlar el
* error, liberar y salir.
*/
void fill_cmd_list(t_cmd_line **cmd_line, char *str, int end, int start)
{
	t_cmd_line	*new;

	new = malloc(sizeof(t_cmd_line));
	if (new == NULL)
		exit_status = 4;
	new->str = NULL;
	new->next = NULL;
	new->str = malloc(sizeof(char) * (end - start + 1));
	if (new->str == NULL)
		exit_status = 4;
	new->str = ft_strncpy(new->str, str + start, end - start);
	ft_lstadd_back(cmd_line, new);
}

/*
* Esta función avanza el puntero del string de command line hasta la posición
* un pipe válido (que no esté entre comillas) y llama a la función que rellena
* la lista con los índices de comienzo y final del comando bien calculados.
*/
void get_cmd_line(char *str, t_cmd_line **cmd_line)
{
	int curr_pos;
	int cmd_start;

	curr_pos = 0;
	cmd_start = 0;
	if (str != NULL)
	{
		while (str[curr_pos])
		{
			// hola | adios
			look_for_pipe(str, &curr_pos);
			fill_cmd_list(cmd_line, str, curr_pos, cmd_start);
			cmd_start = curr_pos;
			cmd_start++;
			curr_pos++;
		}
	}
}

/*
* Función de listas pero adaptada a nuestra estructura. No sé si me convence: NO
*/
void	ft_lstiter(t_cmd_line *lst, void (*f)(char *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		(*f)(lst->str);
		lst = lst->next;
	}
}

/*
* Solo la he hecho para imprimir la lista y comprobar que estuviera llenándose bien
*/
void print_list(char *str)
{
	printf("%s\n", str);
}

void check_redirection(char *str, int *i)
{
	char redirection;

	redirection = str[*i];
	/*Check for <, >, << or >> and get the index to the end of redirection */
	while (str[*i] && str[*i] == redirection)
		(*i)++;
}

void check_arg(char *s, int *i)
{
	t_quote quote;

	quote = NONE;
	while (s[*i])
	{
		if (s[*i] == '"')
		{
			if (quote == NONE)
				quote = DOUBLE;
			else if (quote == DOUBLE)
				quote = NONE;
		}
		if (s[*i] == '\'')
		{
			if (quote == NONE)
				quote = SINGLE;
			else if (quote == SINGLE)
				quote = NONE;
		}
		if ((s[*i] == ' ' || s[*i] == '<' || s[*i] == '>') && quote == NONE)
			break ;
		(*i)++;
	}
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

	token = malloc(sizeof(char *) * (curr_pos - cmd_start + 1));
	if (!token) //en vez de if (token == NULL) ?
		exit_status = 4;
	token->str = NULL;
	token->type = NONE;
	token->exp = false;
	token->next = NULL;
}

void tokenize_cmd(t_cmd_line **cmd)
{
	int curr_pos;
	int cmd_start;

	curr_pos = 0;
	cmd_start = 0;
	while ((*cmd)->str)
	{
		while ((*cmd)->str[curr_pos] == ' ') //Sustituir por ft_ispace?
			curr_pos++;
		cmd_start = curr_pos;
		if ((*cmd)->str[curr_pos])
		{
			if ((*cmd)->str[curr_pos] == '<' || (*cmd)->str[curr_pos] == '>')
				check_redirection((*cmd)->str, &curr_pos);
			else
				check_arg((*cmd)->str, &curr_pos);
			fill_token_list(cmd, (*cmd)->str, curr_pos, cmd_start);
		}
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
		ft_lstiter(cmd_line, print_list);
		/*Aquí iría a continuación:
		*	Tokenizer
		*	Expander
		*	Builtins
		*	Redirecciones
		*	Ejecución
		*/
		tokenizer(cmd_line);
		ft_lstiter(cmd_line, print_list);
		free(str);
	}
	return (0);
}
