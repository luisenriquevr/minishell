/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:44:23 by cristianama       #+#    #+#             */
/*   Updated: 2022/03/02 20:45:17 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "libft.h"

extern int exit_status;

void expand_token(t_token **token)
{

}

void expander(t_cmd_line **cmd_line)
{
    t_cmd_line *cmd;
    t_token *t;

    while (cmd)
    {
        t = cmd->head_token;
        while (t)
        {
            if (t->type == LIMITOR)
                expand_limitor(&t);
            else
                expand_token(&t);
            t = t->next;
        }
        cmd = cmd->next;
    }
}