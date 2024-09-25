/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:43 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/24 22:18:21 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*int    pipe_execution(t_command *command, t_node *node)
{
    t_node  *current_node;

    current_node = node;
    current_node->pid = fork();
    if (current_node->pid == 0)
    {
        if (current_node->fd_out != STDOUT_FILENO)
            dup2(node->fd_out, STDOUT_FILENO);
        if (current_node->fd_in != STDIN_FILENO)
            dup2(current_node->fd_in, STDIN_FILENO);
        run_commands(command, current_node);
        exit(NO_ERROR);
    }
    //waitpid(node->pid, &node->exit_status, 0);
    //close_node_fds(current_node);
    return (NO_ERROR);
}*/

/*int pipe_execution(t_command *command, t_node *node)
{
    t_node *current_node;

    current_node = node;
    current_node->pid = fork();
    if (current_node->pid == 0)  // Processo filho
    {
        // Duplica os file descriptors se forem diferentes de STDOUT/STDIN
        if (current_node->fd_out != STDOUT_FILENO)
            dup2(current_node->fd_out, STDOUT_FILENO);
        if (current_node->fd_in != STDIN_FILENO)
            dup2(current_node->fd_in, STDIN_FILENO);

        // Fechar os descritores desnecessários
        close(current_node->fd_in);
        close(current_node->fd_out);

        // Executa o comando
        run_commands(command, current_node);
        exit(NO_ERROR);
    }
    else if (current_node->pid > 0)  // Processo pai
    {
        // Fechar os descritores de arquivo no processo pai
        if (current_node->fd_in != STDIN_FILENO)
            close(current_node->fd_in);
        if (current_node->fd_out != STDOUT_FILENO)
            close(current_node->fd_out);

        // Esperar pelo processo filho
        waitpid(current_node->pid, &current_node->exit_status, 0);
    }
    else
    {
        // Caso haja erro no fork
        perror("fork");
        return (ERROR);
    }

    return (NO_ERROR);
}*/
