/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:44:23 by cristianama       #+#    #+#             */
/*   Updated: 2022/05/02 10:56:33 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	expand_word_single_quote(char *str, char *dest, int *i)
{
	int		start;
	char	*aux;
	char	*result;

	start = *i;
	aux = NULL;
	result = NULL;
	while (str[*i] != '\'')
		(*i)++;
	aux = (char *)malloc(sizeof(char *) * ((*i) - start + 1));
	if (!aux && dest)
		free(dest);
	else
	{
		aux = ft_strncpy(dest, str + start, (*i) - start);
		result = ft_strjoin(dest, aux);
		free(aux);
		free(dest);
		dest = result;
	}
}
//Idea: juntar estas dos funciones en una con un parámetro type que decida
// cómo tiene que ser la condición del bucle
// bool loop;
// if (!single_quote)
//  loop = str[*i] && str[*i] != '\'' str[*i] != '"' str[*i] != '$';
// else
//  loop = str[*i] != '\'';
void	append_chars(char *str, char *dest, int *i)
{
	int		start;
	char	*aux;
	char	*result;

	start = *i;
	aux = NULL;
	result = NULL;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	aux = (char *)malloc(sizeof(char *) * ((*i) - start + 1));
	if (!aux && dest)
		free(dest);
	else
	{
		aux = ft_strncpy(dest, str + start, (*i) - start);
		result = ft_strjoin(dest, aux);
		free(aux);
		//free(dest);
		dest = result;
	}
}

char	*go_to_var_end(char *str)
{
	while (ft_isalnum(*str) || *str == '_')
		str++;
	return (str);
}

void	expand_var(char *str, char *dest, int *i) //t_token *t, char *str, char *dest, int *i
{
	int	start;
	int	var_length;
	char	*var_name;
	char	*var_content;

	start = *i;
	str++;
	var_length = (int)(go_to_var_end(str) - str);
	var_name = ft_substr(str, *i, var_length);
	(*i) += var_length;
	var_content = getenv(var_name);
	if (!var_content)
	{
		free(var_content);
		return ;
	}
	dest = ft_strjoin(dest, var_content);
	free(var_name);
}

void	check_and_expand_env(char *str, char *dest, int *i)
{
	while (str[*i] && str[*i] != '"' && str[*i] != '\'')
	{
		if (str[*i] == '$')
			expand_var(str, dest, i); /* no quotes expand environment */ //t, str, dest, i
		else
			append_chars(str, dest, i); /* no quotes expand no environment */
	}
}

void	expand_word(t_token *token, t_quote quote, char *str, int *i)
{
	char	*dest;

	dest = ft_strdup("");
	if (quote == NONE || quote == DOUBLE)
		check_and_expand_env(str, dest, i);
	else if (quote == SINGLE)
		expand_word_single_quote(str, dest, i);
	//free(str);
	token->str = dest;
}

t_quote	close_quote(t_quote open, t_quote close, int *i)
{
	close = open;
	(*i)++;
	return (close);
}

void	expand_token(t_token *token)
{
	char	*copy;
	int		i;
	t_quote quote_open;
	t_quote quote_close;

	quote_open = NONE;
	quote_close = NONE;
	copy = ft_strdup(token->str);
	i = 0;
	while (copy[i])
	{
		quote_open = update_quotes(copy[i], quote_open);
		if (quote_open != NONE)
			i++;
		expand_word(token, quote_open, copy, &i);
	}
	if (!copy)
		global.exit_status = 70; //TODO: gestionar error
	//free(token->str);
}

void    expander(t_cmd_line **cmd_line)
{
	t_cmd_line	*cmd;
	t_token		*t;

	cmd = *cmd_line;
	while (cmd)
	{
		t = cmd->head_token;
		while (t)
		{ //Falta aquí comprobar que el token no esté vacío?
			if (t->type == LIMITOR)
				//expand_limitor(t);
				continue;
			else
				expand_token(t);
			t = t->next;
		}
		cmd = cmd->next;
	}
}

