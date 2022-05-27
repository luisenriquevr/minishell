/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:43:47 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/27 18:36:56 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **cmd)
{
	char	*str;

	if (*cmd == NULL)
		return (0);
	str = getcwd(NULL, 0);
	if (str == NULL)
		return (1);
	printf("%s\n", str);
	free(str);
	return (1);
}
