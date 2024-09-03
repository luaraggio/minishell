/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/03 15:49:42 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    run_execve(t_command *command, t_node *list)
{
    t_node  *node;
    char    *path;
    char    **env_array;
    char    **args;
    int     pid;

    pid = 0;
    env_array = envp_list_to_array(command->my_env);
    path = get_absolute_path(command, list);
    if (args_exec(path, list, env_array) == ERROR)
        return (exec_clean(path, env_array), ERROR);
    node = list;
    args = cmds_list_to_array(node);
    //args = node->value;
    pid = fork();
    if (pid == 0)
    {
        if (execve(path, args, env_array) == -1)
        {
            perror("Erro ao executar o comando");
            return (exec_clean(path, env_array), ERROR);
        }
    }
    else if (pid > 0) //father proccess
        waitpid(pid, NULL, 0);
    else
        printf("Deu erro em alguma merda\n");
    return (exec_clean(path, env_array), NO_ERROR);;
}
