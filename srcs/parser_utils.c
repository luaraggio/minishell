/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:43:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/07/05 15:43:48 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int is_metachar(char c)
{
    return (c == '|' || c == '&' || c == ';'
     || c == '(' || c == ')' || c == '<' || c == '>');
}*/

int is_pipe(char c)
{
    return (c == '|');
}

int simple_quote(char c)
{
    return (c == '\'');
}

int double_quote(char c)
{
    return (c == '\"');
}

/*
int is_space_or(char c)
{
    return (c == ' ' || c == '\t');
}
*/