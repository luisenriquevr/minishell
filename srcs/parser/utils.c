/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:15:36 by cmarcu            #+#    #+#             */
/*   Updated: 2022/06/03 20:22:55 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

char	*expand_var(char *str, char *dest)
{
	int		var_length;
	char	*var_name;
	char	*var_content;
	char	*aux;

	var_length = (int)(go_to_var_end(str) - str);
	var_name = ft_substr(str, 1, var_length);
	var_content = get_var(var_name);
	if (!var_content)
	{
		free(var_content);
		return (dest);
	}
	aux = dest;
	dest = ft_strjoin(dest, var_content);
	free(aux);
	free(var_content);
	free(var_name);
	return (dest);
}

void	trim_quotes(t_token *t)
{
	char	*str;
	char	*copy;
	t_quote	quote;

	quote = NONE;
	str = t->str;
	copy = ft_strdup("");
	while (*str)
	{
		quote = update_quotes(*str, quote);
		if (quote != NONE)
			str++;
		while (*str && update_quotes(*str, quote) == quote)
		{
			copy = push_char(copy, *str);
			str++;
		}
		if (quote != NONE)
		{
			str++;
			quote = NONE;
		}
	}
	free(t->str);
	t->str = copy;
}

char	*go_to_var_end_quotes(char *str, t_quote quote)
{
	if (*str != '$')
		return (str);
	str++;
	if (*str == '?')
		return (str);
	if ((*str == '\'' || *str == '"') && quote == NONE)
		return (str);
	if (!ft_isalpha(*str))
		return (str - 1);
	while (ft_isalnum(*str) || *str == '_')
		str++;
	return (str - 1);
}
