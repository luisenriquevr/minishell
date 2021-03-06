/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:06:32 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/29 17:25:55 by lvarela          ###   ########.fr       */
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
	(void)sig;
	g_global.exit_status = 130;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
}

void	process_heredoc(t_token *t, int *fd, char *limitor)
{
	char	*line;

	signal(SIGINT, exit_heredoc);
	line = readline("> ");
	while (line && ft_strcmp(line, limitor) && g_global.exit_status != 130)
	{
		if (t->quote == NONE)
			line = expand_heredoc_line(line);
		write(*fd, line, ft_strlen(line));
		write(*fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
}

int	redir_heredoc(t_token *token, t_cmd_line *cmd, int *fd)
{
	char	*limitor;
	char	*file_name;
	char	*number;

	number = ft_itoa(g_global.nheredoc++);
	file_name = ft_strjoin("/tmp/_tmp", number);
	free(number);
	*fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	limitor = token->str;
	if (*fd < 0)
		return (throw_error("minishell: error: redirection"));
	signal(SIGINT, SIG_IGN);
	process_heredoc(token, fd, limitor);
	close(*fd);
	if (cmd->head_token->type != HERE_DOC)
		*fd = open(file_name, O_RDONLY, 0644);
	if (cmd->fd_in)
		close(cmd->fd_in);
	cmd->fd_in = *fd;
	free(file_name);
	signal(SIGINT, handle_signal);
	return (g_global.exit_status);
}
