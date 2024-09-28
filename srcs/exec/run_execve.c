/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/28 17:04:04 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    run_execve(t_command *command, t_node *list)
{
    t_node      *node;
    char        *path;
    char        **env_array;
    char        **args;

    env_array = envp_list_to_array(command->my_env);
    if (access(list->token->word, X_OK) != 0) // verificar acesso em outra função mais completa!!!
        path = get_executable_path(command, list);
    else
        path = list->token->word;
    node = list;
    args = cmd_list_to_array(node);
    node->pid = fork();
    if (node->pid == 0)
    {
        if (node->fd_out != STDOUT_FILENO)
        {
            if (dup2(node->fd_out, STDOUT_FILENO) == -1)
            {
                perror("dup2 fd_out");
                execve_clean(path, args, env_array);
                exit(ERROR);
            }
            close(node->fd_out);
        }
        if (node->fd_in != STDIN_FILENO)
        {
            if (dup2(node->fd_in, STDIN_FILENO) == -1)
            {
                perror("dup2 fd_in");
                execve_clean(path, args, env_array);
                exit(ERROR);
            }
            close(node->fd_in);
        }
        if (execve(path, args, env_array) == -1)
        {
            execve_clean(path, args, env_array);
            exit(127);
        }
    }
    waitpid(node->pid, &node->exit_status, 0);
    execve_clean(path, args, env_array);
    return (NO_ERROR);
}
