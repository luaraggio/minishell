/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/17 12:41:56 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    run_execve(t_command *command, t_node *list)
{
    int     exit_status;
    extern volatile unsigned int	g_status;
    t_node      *node;
    char        *path;
    char        **env_array;
    char        **args;

    exit_status = (int) g_status;
    env_array = envp_list_to_array(command->my_env);
    path = get_absolute_path(command, list);
    node = list;
    args = cmd_list_to_array(node);
    list->pid = fork();
    if (list->pid == 0)
    {
        if (execve(path, args, env_array) == -1)
        {
            my_putstr_fd("Command cannot execute\n", STDERR_FILENO);
            return (execve_clean(path, env_array), free_matrix(args), g_status = 126,
            ERROR);
        }
    }
    else if (list->pid > 0) //father proccess
        waitpid(list->pid, &exit_status, 0);
    else
        printf("Deu alguma merda no pid\n");
    return (execve_clean(path, env_array), free_matrix(args), NO_ERROR);
}
