/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:29:45 by cristianama       #+#    #+#             */
/*   Updated: 2022/06/03 17:26:36 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

char	*go_to_var_end(char *str)
{
	if (*str != '$')
		return (str);
	str++;
	if (*str == '?')
		return (str);
	if (!ft_isalpha(*str))
		return (str - 1);
	while (ft_isalnum(*str) || *str == '_')
		str++;
	return (str - 1);
}

char	*push_char(char *str, char c)
{
	int		str_length;
	char	*result;

	if (!str)
		return (NULL);
	if (!c)
	{
		result = ft_strdup(str);
		free(str);
		return (result);
	}
	str_length = ft_strlen(str);
	result = malloc(str_length + 2);
	ft_memcpy(result, str, str_length);
	*(result + str_length) = c;
	*(result + str_length + 1) = '\0';
	free(str);
	return (result);
}

bool	not_expand(char c, t_quote quote)
{
	if (c == '$' && quote == SINGLE)
		return (true);
	return (false);
}

void	expand_token(t_token *token)
{
	char	*copy;
	char	*result;
	t_quote	quote;

	copy = token->str;
	result = ft_strdup("");
	quote = NONE;
	while (*copy)
	{
		if (not_expand(*copy, quote) || go_to_var_end_quotes(copy, quote) == copy)
			result = push_char(result, *copy);
		else
		{
			result = expand_var(copy, result);
			copy = go_to_var_end(copy);
		}
		quote = update_quotes(*copy, quote);
		copy++;
	}
	free(token->str);
	token->str = result;
}

void	expander(t_cmd_line **cmd_line)
{
	t_cmd_line	*cmd;
	t_token		*t;

	cmd = *cmd_line;
	while (cmd)
	{
		t = cmd->head_token;
		while (t)
		{
			if (t->type == LIMITOR)
				trim_quotes(t);
			else
			{
				expand_token(t);
				trim_quotes(t);
			}
			t = t->next;
		}
		cmd = cmd->next;
	}
}
