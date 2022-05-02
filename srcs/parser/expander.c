/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:29:45 by cristianama       #+#    #+#             */
/*   Updated: 2022/05/02 13:49:19 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
char	*expand_var(char *str, char *dest) //t_token *t, char *str, char *dest, int *i
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

