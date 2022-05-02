/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:29:45 by cristianama       #+#    #+#             */
/*   Updated: 2022/05/02 19:47:11 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
char	*expand_var(char *str, char *dest)
{
	int		var_length;
	char	*var_name;
	char	*var_content;

	var_length = (int)(go_to_var_end(str) - str);
	var_name = ft_substr(str, 1, var_length);
	var_content = getenv(var_name);
	if (!var_content)
	{
		free(var_content);
		return (dest);
	}
	dest = ft_strjoin(dest, var_content);
	free(var_name);
	return (dest);
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

bool	may_expand(char c, bool expand)
{
	if (c == '$')
		return (!expand);
	return (false);
}

bool	update_may_expand(char c, bool expand)
{
	if (c == '\'')
		return (!expand);
	return (expand);
}

void	expand_token(t_token *token)
{
	char	*copy;
	char	*result;
	bool	expand;

	copy = token->str;
	result = ft_strdup("");
	expand = true;
	while (*copy)
	{
		if (may_expand(*copy, expand) || go_to_var_end(copy) == copy)
			result = push_char(result, *copy);
		else
		{
			result = expand_var(copy, result);
			copy = go_to_var_end(copy);
		}
		expand = update_may_expand(*copy, expand);
		copy++;
	}
	free(token->str);
	token->str = result;
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
	}
	free(t->str);
	t->str = copy;
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

