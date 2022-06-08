/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:34:42 by lvarela           #+#    #+#             */
/*   Updated: 2022/06/08 19:09:08 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(char *str, t_cmd_line **cmd_line)
{
	if (str == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	if (check_str(str))
		return (0);
	if (!only_space(str))
		return (0);
	if (get_cmd_line(str, cmd_line))
		exit_free_cmdline(cmd_line);
	if (tokenizer(cmd_line))
		exit_free_cmdline(cmd_line);
	expander(cmd_line);
	g_global.exit_status = 0;
	prepare_exec(cmd_line);
	redirector(cmd_line);
	return (1);
}
