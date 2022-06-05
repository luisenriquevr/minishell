/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:23:51 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/05 21:56:41 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_out_file(t_token *token, t_cmd_line *cmd, int *fd)
{
	if (token->type == OUT_FILE)
		*fd = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		*fd = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*fd < 0)
		return (throw_error("Error: redirection"));
	if (cmd->fd_out)
		close(cmd->fd_out);
	cmd->fd_out = *fd;
	return (0);
}

int	redir_in_file(t_token *token, t_cmd_line *cmd, int *fd)
{
	*fd = open(token->str, O_RDONLY);
	if (*fd < 0)
		return (throw_error("minishell: error: redirection"));
	if (cmd->fd_in)
		close(cmd->fd_in);
	cmd->fd_in = *fd;
	return (0);
}

int	redirection(t_token *token, t_cmd_line *cmd)
{
	int	fd;

	fd = 0;
	if (token->type == IN_FILE)
		return (redir_in_file(token, cmd, &fd));
	if (token->type == OUT_FILE || token->type == OUT_FILE_APPEND)
		return (redir_out_file(token, cmd, &fd));
	if (token->type == LIMITOR)
		return (redir_heredoc(token, cmd, &fd));
	if (fd)
		close(fd);
	return (0);
}

void	redirector(t_cmd_line **cmd_line)
{
	t_cmd_line	*cmd;
	t_token		*token;

	cmd = *cmd_line;
	while (cmd && g_global.exit_status != 130)
	{
		token = cmd->head_token;
		while (token)
		{
			if (redirection(token, cmd))
			{
				cmd->exec = false;
				break ;
			}
			token = token->next;
		}
		cmd = cmd->next;
	}
}
