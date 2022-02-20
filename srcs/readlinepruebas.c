/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readlinepruebas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:36:17 by cmarcu            #+#    #+#             */
/*   Updated: 2022/02/20 14:24:07 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>

int exit_status; //Variable global

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
			look_for_pipe(str, &curr_pos);
			fill_cmd_list(cmd_line, str, curr_pos, cmd_start);
			cmd_start = curr_pos;
			cmd_start++;
			curr_pos++;
		}
	}
}

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

void print_list(char *str)
{
	printf("%s\n", str);
}

int main(void)
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
		free(str);
	}
	return (0);
}
