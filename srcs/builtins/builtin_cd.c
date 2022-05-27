/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:00:07 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/27 19:44:59 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_pwd(void)
{
	char	*tmp;
	char	*old_path;
	char	*new_path;
	char	*pwd;

	pwd = get_var("PWD");
	old_path = ft_strjoin("OLDPWD=", pwd);
	tmp = getcwd(NULL, 1000);
	new_path = ft_strjoin("PWD=", tmp);
	change_var("PWD", new_path);
	change_var("OLDPWD", old_path);
	free(old_path);
	free(tmp);
	free(new_path);
	if (pwd)
		free(pwd);
}

void	old_pwd(char **path)
{
	free(*path);
	*path = get_var("OLDPWD");
	printf("%s\n", *path);
}

char	*change_home(char *path)
{
	char	*tmp1;
	char	*tmp2;

	if (path[0] == '~')
		tmp1 = get_var("HOME");
	if (path[1] != '/')
	{
		tmp2 = ft_strjoin(tmp1, "/");
		free(tmp1);
		tmp1 = tmp2;
	}
	tmp2 = ft_strjoin(tmp1, (path + 1));
	if (path)
		free(path);
	path = tmp2;
	free(tmp1);
	return (path);
}

int	builtin_cd(char **arg)
{
	char	*path;

	if (!global.env)
	{
		if (array_length(arg) > 2)
			throw_error("cd: too many arguments\n");
		if (!arg[1])
			path = get_var("HOME");
		else
			path = ft_strdup(arg[1]);
		if (path && path[0] == '~')
			path = change_home(path);
		if (path && path[0] == '-' && !path[1])
			old_pwd(&path);
		if (chdir(path) < 0)
		{
			printf("cd: string not in pwd: %s\n", path);
			free(path);
			return (1);
		}
		if (path)
			free(path);
		new_pwd();
	}
	return (1);
}
