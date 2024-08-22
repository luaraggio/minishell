/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/08/21 16:30:15 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    run_execve(t_command *command, t_node *list)
{
    t_node  *node;
    char    *path;
    char    **env_array;
    char    **args;

    env_array = envp_list_to_array(command->my_env);
    path = get_absolute_path(command, list);
    if (args_exec(path, list, env_array) == ERROR)
        return (exec_clean(path, env_array), ERROR);
    node = list;
    args = node->value;
    if (execve(path, args, env_array) == -1)
    {
        perror("Erro ao executar o comando");
        return (exec_clean(path, env_array), ERROR);
    }
    return (exec_clean(path, env_array), NO_ERROR);;
}
