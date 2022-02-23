/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:23:05 by cmarcu            #+#    #+#             */
/*   Updated: 2022/02/23 20:43:10 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <stdbool.h>

/*
* Hay que declarar todas las listas antes de definirlas para que el *next pueda
* ser del tipo de la lista
*/
typedef struct s_cmd_line t_cmd_line;
typedef struct s_token s_token;

struct s_cmd_line
{
	char 		*str;
	t_cmd_line	*next;
};

struct s_token
{
	char *str;
	int type;
	t_token *next;
};

typedef enum quote
{
	NONE,
	SINGLE,
	DOUBLE,
	END
}	t_quote;

#endif
