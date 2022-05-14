/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 09:28:52 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/13 17:58:14 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	slashjoin(char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
}

char	*get_path(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (global.env[i][j])
	{
		if (!ft_strncmp(&global.env[i][j], "PATH", 4))
			return (&global.env[i][j]);
		else
			i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("$PATH not found\n", 2);
	return (NULL);
}

char	**paths_pull(void)
{
	char	*path;
	int		i;
	char	**all_paths;

	path = get_path();
	i = 0;
	while (path && path[i++] != '=');
	all_paths = ft_split(&path[++i], ':');
	slashjoin(all_paths);
	return (all_paths);
}

int	checker(char **cmd_to_exec, char **path)
{
	int		i;
	char	*tmp_cmd;

	i = -1;
	while (path[++i])
	{
		tmp_cmd = ft_strjoin(path[i], cmd_to_exec[0]);
		if (!access(tmp_cmd, X_OK))
		{
			cmd_to_exec[0] = tmp_cmd;
			array_free(path);
			return (0);
		}
		free(tmp_cmd);
	}
	return (1);
}

int	access_checker(char **cmd_to_exec)
{
	char	**path;


	path = paths_pull();
	if (!path || !*cmd_to_exec)
	{
		array_free(path);
		return (0);
	}
	if (access(cmd_to_exec[0], X_OK))
		return (checker(cmd_to_exec, path));
	return (1);
}
