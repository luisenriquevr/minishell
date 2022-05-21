/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:27:21 by cristianama       #+#    #+#             */
/*   Updated: 2022/05/21 14:18:17 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

void	print_list(char *str)
{
	printf("%s\n", str);
}

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
