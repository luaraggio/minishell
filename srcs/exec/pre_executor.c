/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:55:49 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/19 09:59:07 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Função p/ percorrer node e organizar os fds

void    clean_pipe(t_node *node)
{
    free_list(node);
}
*/

//VERIFICAR DUP???

void    configure_fd(t_command *command, t_node *sentence)
{
    t_node  *current_node;

    current_node = sentence;
    while (current_node)
    {
        
    }
}
