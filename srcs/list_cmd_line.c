/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:27:21 by cristianama       #+#    #+#             */
/*   Updated: 2022/02/26 13:01:37 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

extern int exit_status;

/*
* Función de listas pero adaptada a nuestra estructura. No sé si me convence
*/
t_cmd_line	*ft_lstlast(t_cmd_line *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/*
* Función de listas pero adaptada a nuestra estructura. No sé si me convence
*/
void	ft_lstadd_back(t_cmd_line **lst, t_cmd_line *new)
{
	t_cmd_line *last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
/*
* Función de listas pero adaptada a nuestra estructura. No sé si me convence: NO
*/
void	ft_lstiter(t_cmd_line *lst, void (*f)(char *))
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
void print_list(char *str)
{
	printf("%s\n", str);
}