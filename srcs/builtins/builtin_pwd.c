/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvarela <lvarela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:43:47 by lvarela           #+#    #+#             */
/*   Updated: 2022/05/08 17:54:39 by lvarela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_pwd(char **cmd)
{
	char	*str;
	
	if (*cmd == NULL)
		return (0);
	str = getcwd(NULL, 0); // Devuelve el string con malloc hecho o NULL si ha habido error
	if (str == NULL)
		return (1); // Tenemos que ver lo de devolver errores
	printf("%s\n", str);
	free(str);
	return (1);
}
