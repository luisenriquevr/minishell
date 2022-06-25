/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:06:32 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/25 19:00:06 by lvarela          ###   ########.fr       */
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

void	child_process_heredoc(int *fd, char *limitor)
{
	char	*line;

	signal(SIGINT, exit_heredoc);
	line = readline("> ");
	while (line && ft_strcmp(line, limitor) && g_global.exit_status != 130)
	{
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
	child_process_heredoc(fd, limitor);
	signal(SIGINT, handle_signal);
	close(*fd);
	*fd = open(file_name, O_RDONLY, 0644);
	if (cmd->fd_in)
		close(cmd->fd_in);
	cmd->fd_in = *fd;
	free(file_name);
	return (g_global.exit_status);
}

/* TODO: Tenemos el problema de que si nos cierran el heredoc con señales,	*
 * dejamos abiertos los fd. Seguramente si hiciesemos el heredoc en un		*
 * hijo no tendríamos este problema, pero tendríamos los del pasado. 		*/
