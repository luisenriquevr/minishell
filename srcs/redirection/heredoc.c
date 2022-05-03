/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:06:32 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/03 21:57:16 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*expand_heredoc_line(char *line)
{
	char	*copy;
	char	*result;

	copy = line;
	result = ft_strdup("");
	while (*copy)
	{
		if (go_to_var_end(copy) == copy)
			result = push_char(result, *copy);
		else
		{
			result = expand_var(copy, result);
			copy = go_to_var_end(copy);
		}
		copy++;
	}
	free(line);
	line = result;
	return (line);
}

int	redir_heredoc(t_token *token, int *fd)
{
	char	*line;
	char	*limitor;

	*fd = open("/tmp/_tmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	limitor = token->str;
	line = readline(">");
	if (*fd < 0)
		return (throw_error("Error: redirection"));
	while (line && !ft_strcmp(line, limitor))
	{
		line = expand_heredoc_line(line);
		write(*fd, line, ft_strlen(line));
		write(*fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(line);
	close(*fd);
	*fd = open("/tmp/_tmp", O_RDONLY | O_CREAT | O_SYMLINK, 0644);
	dup2(*fd, STDIN_FILENO);
	close(*fd);
	return (0);
}
