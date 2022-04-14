/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:39:57 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/11 20:47:30 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

bool	check_builtin(char *arg)
{
	/*
	* Los builtins son> echo, cd, pwd, export, unset, env, exit.
	*/
	if (arg != NULL)
	{
		if (ft_strcmp(arg, "echo") || ft_strcmp(arg, "export") 
		|| ft_strcmp(arg, "unset") || ft_strcmp(arg, "exit")
		|| ft_strcmp(arg, "env") || ft_strcmp(arg, "cd")
		|| ft_strcmp(arg, "pwd"))
			return (true);

	}
	return (false);
}

t_quote	update_quotes(char c, t_quote quote)
{
	if (c == '"')
	{
		if (quote == NONE)
			quote = DOUBLE;
		else if (quote == DOUBLE)
			quote = NONE;
	}
	if (c == '\'')
	{
		if (quote == NONE)
			quote = SINGLE;
		else if (quote == SINGLE)
			quote = NONE;
	}
	return (quote);
}
/*
* Esta función recibe por parámetro la línea de comandos y cuando encuentra
* una comilla del tipo que sea setea el tipo de comillas a ese tipo y hasta
* que no vuelve a encontrar una igual no lo cambia.
* Si cuando acaba el tipo de comilla es distinto de NONE significa que alguna
* se ha quedado sin cerrar y tenemos que gestionar el error, liberar lo que
* sea y salir.
*/
int	check_quotes(char *str)
{
	t_quote	quote;
	int		i;

	quote = NONE;
	i = 0;
	while (str[i])
	{
		quote = update_quotes(str[i], quote);
		i++;
	}
	if (quote != NONE) //TODO: gestionar error
		return (errcode_print_return(14, "Unclosed quotes")); //Las comillas no están cerradas
	return (0);
}

/*
* Esta función está MAL (líneas 67-69)
*/
int	check_str(char *str)
{
	int		i;
	bool	after_pipe;

	i = 0;
	after_pipe = false;
	if (str == NULL) //TODO: gestionar error
		return (errcode_print_return(10, "No arguments")); //Probablemente esto acabe siendo una función que libere todo lo que hayamos alojado y pase el exit_status como parámetro
	while (str[i])
	{
		// "     cat    |  echo | blah |"
		while (str[i] == ' ')
			i++;
		if (str[i] == '|')
		{
			if (!after_pipe) //TODO: gestionar error
				return (errcode_print_return(12, "Syntax error")); //tendremos que ponernos de acuerdo para un conjunto de estados de error :)

			after_pipe = true;
		}
		i++;
	}
	if (check_quotes(str))
		return (1);
	return (0);
}

void check_redirection(char *str, int *i)
{
	char	redirection;

	redirection = str[*i];
	/*Check for <, >, << or >> and get the index to the end of redirection */
	while (str[*i] && str[*i] == redirection)
		(*i)++;
}

void check_arg(char *s, int *i)
{
	t_quote	quote;

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