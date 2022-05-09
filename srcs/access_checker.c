/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 09:28:52 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/09 12:28:39 by lvarela          ###   ########.fr       */
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
	perror("$PATH's error"); // aqui deberia de haber un throw error
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
			//free(cmd_to_exec[0]); // da error pero hay que liberar
			//printf("%s\n", tmp_cmd);
			cmd_to_exec[0] = tmp_cmd;
			free(tmp_cmd);
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
	if (access(cmd_to_exec[0], X_OK) != 0)
		return (checker(cmd_to_exec, path)); // quizas haya que dar error si no hay acceso de ninguna manera
	return (1);
}
