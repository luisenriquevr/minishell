/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:44:23 by cristianama       #+#    #+#             */
/*   Updated: 2022/03/05 23:44:16 by cristianama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "libft.h"

void expand_word_single_quote(char *str, char *dest, int *i)
{
    int start;
    char *aux;
    char *result;

    start = *i;
    aux = NULL;
    result = NULL;
    while (str[*i] != '\'')
        (*i)++;
    aux = (char *)malloc(sizeof(char *) * ((*i) - start + 1));
    if (!aux && dest)
        free(dest);
    else
    {
        aux = ft_strncpy(dest, str + start, (*i) - start);
        result = ft_strjoin(dest, aux);
        free(aux);
        free(dest);
        dest = result;
    }
}
//Idea: juntar estas dos funciones en una con un parámetro type que decida
// cómo tiene que ser la condición del bucle
// bool loop;
// if (!single_quote)
//  loop = str[*i] && str[*i] != '\'' str[*i] != '"' str[*i] != '$';
// else
//  loop = str[*i] != '\'';
char *expand_no_env(char *str, char *dest, int *i)
{
    int start;
    char *aux;
    char *result;

    start = *i;
    aux = NULL;
    result = NULL;
    while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
        (*i)++;
    aux = (char *)malloc(sizeof(char *) * ((*i) - start + 1));
    if (!aux && dest)
        free(dest);
    else
    {
        aux = ft_strncpy(dest, str + start, (*i) - start);
        result = ft_strjoin(dest, aux);
        free(aux);
        free(dest);
        dest = result;
    }
}

void check_and_expand_env(t_token *t, char *str, char *dest, int *i)
{
    if (str[*i] == '$')
        dest = NULL; //Hasta que se desarrolle: expand_env(t, str, dest, &i);
    else
        dest = expand_no_env(str, dest, i);
}

void expand_word(t_token *token, t_quote quote, char *str, int *i)
{
    //Debería meter aquí la comprobación de que dst != NULL?
    // while (str && str[*cur] && str[*cur] != '"') //double
    // while (str[*cur] && str[*cur] != '\'' && str[*cur] != '"') //none
    // while (str && str[(*i)] && str[(*i)] != '\'') //single

    char *dest;

    dest = NULL;
    while (str && str[*i])
    {
        if (quote == NONE)
            while (str[*i] && str[*i] != '\'' && str[*i] != '"')
                check_and_expand_env(token, str, dest, i);
        else if (quote == DOUBLE)
            while (str[*i] && str[*i] != '"')
                check_and_expand_env(token, str, dest, i);
        else if (quote == SINGLE)
            expand_word_single_quote(str, dest, i);
    }
    free(str);
    token->str = dest;
}

void close_quote(t_quote *open, t_quote *close, int *i)
{
    close = open;
    (*i)++;
}

void expand_token(t_token *token)
{
    char *copy;
    int i;
    t_quote quote_open;
    t_quote quote_close;

    quote_open = NONE;
    quote_close = NONE;
    copy = ft_strdup(token->str);
    free(token->str);
    i = 0;
    while (str[i])
    {
        update_quotes(str[i], &quote_open);
        if (quote_open != quote_close)
            close_quote(&quote_open, &quote_close, &i);
        else
            expand_word(token, quote_open, copy, &i);
    }
    if (!copy)
        global.exit_status = 70;
}

void expander(t_cmd_line **cmd_line)
{
    t_cmd_line *cmd;
    t_token *t;

    cmd = *cmd_line;
    while (cmd)
    {
        t = cmd->head_token;
        while (t)
        { //Falta aquí comprobar que el token no esté vacío?
            if (t->type == LIMITOR)
                //expand_limitor(t);
                continue;
            else
                expand_token(t);
            t = t->next;
        }
        cmd = cmd->next;
    }
}