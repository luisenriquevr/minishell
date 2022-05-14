/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:06:32 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/14 01:06:02 by lvarela          ###   ########.fr       */
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

void	exit_heredoc(int sig)
{
	global.exit_status += sig;
	if (sig == 2)
	{
		global.exit_status = 130;
		//ft_putstr_fd("\n", sig);
		exit (1);
	}
}

int	redir_heredoc(t_token *token, t_cmd_line *cmd, int *fd)
{
	char	*line;
	char	*limitor;
	pid_t	pid;

	*fd = open("/tmp/_tmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	limitor = token->str;
	if (*fd < 0)
			return (throw_error("Error: redirection"));
	pid = fork();
	if (!pid)
	{
		line = readline("> ");
		while (line && ft_strcmp(line, limitor))
		{
			signal(SIGINT, exit_heredoc);
			line = expand_heredoc_line(line);
			write(*fd, line, ft_strlen(line));
			write(*fd, "\n", 1);
			free(line);
			line = readline("> ");
		}
		free(line);
		exit(1);
	}
	else if (pid)
		waitpid(-1, &global.exit_status, 0);
	else
		perror("Error: fork");
	close(*fd);
	*fd = open("/tmp/_tmp", O_RDONLY, 0644);
	if (cmd->fd_in)
		close(cmd->fd_in);
	cmd->fd_in = *fd;
	return (0);
}
