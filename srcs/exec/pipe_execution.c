/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:43 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/26 19:55:31 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    pipe_execution(t_command *command, t_node *node)
{
    t_node  *current_node;

    current_node = node;
    node->pid = fork();
    if (node->pid == 0)
    {
        if (node->fd_out != STDOUT_FILENO)
            dup2(node->fd_out, STDOUT_FILENO);
        if (node->fd_in != STDIN_FILENO)
            dup2(node->fd_in, STDIN_FILENO);
        run_commands(command, node);
        exit(NO_ERROR);
        //Ver se precisa fechar fd aqui!!!
    }
    waitpid(current_node->pid, &node->exit_status, 0);
    return (NO_ERROR);
}
