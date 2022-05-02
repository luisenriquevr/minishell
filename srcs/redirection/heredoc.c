/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:06:32 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/02 19:37:00 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_heredoc(t_token *token, int *fd)
{
	char	*line;
	char	*end;

	*fd = open("/tmp/_tmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	end = token->str;
	line = readline(">");
	if (*fd < 0)
		return (throw_error("Error: redirection"));
	while (line && !ft_strcmp(line, end))
	{
		write(*fd, line, ft_strlen(line));
		write(*fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(line);
	close(*fd);
	*fd = open("/tmp/_tmp", O_RDONLY | O_CREAT | O_SYMLINK, 0644);
	return (0);
}
