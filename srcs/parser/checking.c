/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:39:57 by cristianama       #+#    #+#             */
/*   Updated: 2022/05/21 16:51:07 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

bool	check_builtin(char *arg)
{
	if (arg != NULL)
	{
		if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "export")
			|| !ft_strcmp(arg, "unset") || !ft_strcmp(arg, "exit")
			|| !ft_strcmp(arg, "env") || !ft_strcmp(arg, "cd")
			|| !ft_strcmp(arg, "pwd"))
			return (true);
	}
	return (false);
}

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
	if (quote != NONE)
		return (errcode_print_return(14, "minishell: unclosed quotes\n"));
	return (0);
}

int	check_str(char *str)
{
	int		i;
	bool	pipe_allowed;

	i = 0;
	pipe_allowed = false;
	if (!str)
		return (global.exit_status = 10);
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] != '|')
			pipe_allowed = true;
		if (str[i] == '|')
		{
			if (!pipe_allowed)
				return (errcode_print_return(12, "minishell: syntax error\n"));
			pipe_allowed = true;
		}
		if (str[i])
			i++;
	}
	if (check_quotes(str))
		return (1);
	return (0);
}

void	check_redirection(char *str, int *i)
{
	char	redirection;

	redirection = str[*i];
	while (str[*i] && str[*i] == redirection)
		(*i)++;
}

void	check_arg(char *s, int *i)
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
		if ((s[*i] == ' ' || s[*i] == '\t' || s[*i] == '<'
				|| s[*i] == '>') && quote == NONE)
			break ;
		(*i)++;
	}
}


// echo $ "$'$USER'$ "''
// echo $'$'$USER'$ '''
// echo $'$'$USER'$ '''$
// echo $"hola"$""
// echo $"$'$USER'$ "''$ "$USER"
// echo $"$'$USER'$ "''$"$USER"
// echo $'$USER'
// echo $"$USER"
// echo $'$'$USER''
// echo $"$USER"
