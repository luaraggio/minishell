/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:43 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/28 17:27:30 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    pipe_execution(t_command *command, t_node *node)
{
    if (node->pid == 0)
    {
        if (node->fd_out != STDOUT_FILENO)
            dup2(node->fd_out, STDOUT_FILENO);
        if (node->fd_in != STDIN_FILENO)
            dup2(node->fd_in, STDIN_FILENO);
        //run_pipe_commands(command, node);
        exit(NO_ERROR);
    }
    close_node_fds(node);
    waitpid(node->pid, &node->exit_status, 0);
    return (NO_ERROR);
}
