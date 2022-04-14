/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 09:28:52 by lvarela           #+#    #+#             */
/*   Updated: 2022/03/07 15:53:46 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	*get_path(char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i][j])
	{
		if (!ft_strncmp(&envp[i][j], "PATH", 4))
			return (&envp[i][j]);
		else
			i++;
	}
	perror("$PATH's error"); // aqui deberia de haber un throw error
	return (NULL);
}

char	**paths_pull(char **envp)
{
	char	*path;
	int	i;
	char	**all_paths;
	
	path = get_path(envp);
	i = 0;
	while (path && path[i++] != '=');
	all_paths = ft_split(&path[++i], ':');
	slashjoin(all_paths);
	return (all_paths);
}

void	checker(char **cmd_to_exec, char **path)
{
	int		i;
	char	*tmp_cmd;
	
	i = -1;
	while (path[++i])
	{
		tmp_cmd = ft_strjoin(path[i], cmd_to_exec[0]);
		if (!access(tmp_cmd, X_OK))
		{
			// free(*cmd_to_exec); // da error pero hay que liberar
			cmd_to_exec[0] = ft_strdup(tmp_cmd);
		}
	}
}

int		access_checker(char **cmd_to_exec, char **envp)
{
	char	**path;
	char	*tmp_cmd;
	
	path = paths_pull(envp);
	tmp_cmd = NULL;
	if (!path || !*cmd_to_exec)
	{
		free(path);
		return (0);
	}
	if (access(cmd_to_exec[0], X_OK) != 0)
		checker(cmd_to_exec, path); // quizas haya que dar error si no hay acceso de ninguna manera
	return (1);
}