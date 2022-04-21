/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:27:21 by cristianama       #+#    #+#             */
/*   Updated: 2022/04/21 21:36:02 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
* Función de listas pero adaptada a nuestra estructura.
*/

void	lstadd_back_cmd(t_cmd_line **lst, t_cmd_line *new)
{
	t_cmd_line	*last;

	if (lst)
	{
		last = *lst;
		if (last == NULL)
			*lst = new;
		else
		{
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
}
/*
* Función de listas pero adaptada a nuestra estructura.
*/

void	lstiter_cmd(t_cmd_line *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		(*f)(lst->str);
		lst = lst->next;
	}
}

/*
* Solo la he hecho para imprimir la lista y comprobar que estuviera llenándose bien
*/

void	print_list(char *str)
{
	printf("%s\n", str);
}

/*
* Función de listas pero adaptada a nuestra estructura.
*/

void	lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst)
	{
		last = *lst;
		if (last == NULL)
			*lst = new;
		else
		{
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
}
