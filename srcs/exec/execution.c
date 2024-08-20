/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/08/20 13:29:29 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char     *get_path_var(t_command *command)
{
    t_env   *get_path; //permite armazenar o resultado de "path" a partir da nossa envp
    char    *path;

    get_path = my_getenv_by_list("PATH", command->my_env);
    if (!get_path)
    {
        perror("Erro: Variável PATH não encontrada");
        return (NULL);
    }
    path = get_path->value;
    //printf("%s=%s\n", get_path->key, get_path->value);
    return (path);
}

char    *get_absolute_path(t_command *command, t_node *node)
{
    const char  *command_name;
    char    *path;
    char    **dir;
    char    *absolute_path;
    int     i;

    i = 0;
    command_name = node->value[0];
    path = get_path_var(command);
    if (!path)
        return (NULL);
    dir = my_split(path, ':');
    if (!dir)
        return (NULL);
    while (dir[i])
    {
        absolute_path = my_strjoin(dir[i], "/");
        absolute_path = my_strjoin(absolute_path, command_name);
        if (access(absolute_path, X_OK) == 0)
        {
            free_matrix(dir);
            return(absolute_path);
        }
        free(absolute_path);
        i++;
    }
    free_matrix(dir);
    return (NULL);
}

int    run_execve(t_command *command, t_node *list) //-> mudar o retorno para int!
{
    t_node  *node;
    char    *path;
    char    **env_array;
    char    **args;

    if (!list || !list->value)
    {
        perror("Erro na lista de comandos");
        return (ERROR);
    }
    node = list;
    args = node->value;
    env_array = envp_list_to_array(command->my_env);
    if (!env_array)
    {
        perror("Erro ao converter lista de ambiente para array");
        return (ERROR);
    }
    path = get_absolute_path(command, list);
    if (!path)
    {
        free(env_array);
        printf("Erro: Comando '%s' não encontrado\n", list->value[0]);
        return (ERROR);

    }
    if (execve(path, args, env_array) == -1)
    {
        perror("Erro ao executar o comando");
        free(env_array);
        free(path);
        return (ERROR);
    }
    free(env_array);
    free(path);
    return (NO_ERROR);
}
