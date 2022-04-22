/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:23:51 by lvarela           #+#    #+#             */
/*   Updated: 2022/04/22 19:15:09 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int				redir_out_file(t_token *token, int *fd)
{
	if (token->type == OUT_FILE)
		*fd = open(token->str, O_CREAT | O_WRONLY, 0644);
	else
		*fd = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*fd < 0)
		return (throw_error("Error: redirection"));
	if (dup2(*fd, STDOUT_FILENO) < 0)
		return (throw_error("Error: redirection"));
	return (0);
}

int				redir_in_file(t_token *token, int *fd)
{
	*fd = open(token->str, O_RDONLY);
	if (*fd < 0)
		return (throw_error("Error: redirection"));
	if (dup2(*fd, STDIN_FILENO) < 0)
		return (throw_error("Error: redirection"));
	return (0);
}

int				redirection(t_token *token)
{
	int			fd;

	fd = 0;
	global.fd_stdin = dup(1);
	global.fd_stdout = dup(0);
	if (token->type == IN_FILE)
		return (redir_in_file(token, &fd));
	if (token->type == OUT_FILE || token->type == OUT_FILE_APPEND)
		return (redir_out_file(token, &fd));
	//if (token->type == LIMITOR)
	//	return (redir_heredoc(token, &fd));
	if (fd)
		close(fd);
	return (0);
}

void			redirector(t_cmd_line **cmd_line)
{
	t_cmd_line	*cmd;
	t_token		*token;

	cmd = *cmd_line;
	while (cmd)
	{
		token = cmd->head_token;
		while (token)
		{
			global.redir_error = redirection(token);
			token = token->next;
		}
		cmd = cmd->next;
	}
}