/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:07:06 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/03 15:51:40 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char     *get_path_var(t_command *command)
{
    t_env   *get_path;
    char    *path;

    get_path = my_getenv_by_list("PATH", command->my_env);
    if (!get_path)
        return (perror("Erro: Variável PATH não encontrada"), NULL);
    path = get_path->value;
    return (path);
}

char    *get_absolute_path(t_command *command, t_node *node)
{
    char    *path;
    char    **dir;
    char    *absolute_path;
    int     i;

    i = 0;
    path = get_path_var(command);
    if (!path)
        return (NULL);
    dir = my_split(path, ':');
    if (!dir)
        return (NULL);
    while (dir[i])
    {
        absolute_path = my_strjoin(dir[i], "/");
        absolute_path = my_strjoin(absolute_path, node->value[0]);
        if (access(absolute_path, X_OK) == 0)
            return (free_matrix(dir), absolute_path);
        free(absolute_path);
        i++;
    }
    return (free_matrix(dir), NULL);
}

char    **envp_list_to_array(t_env *env_list)
{
    int         i; //quantidade de args
    char        **array;

    if (!env_list)
        return (NULL);
    i = env_list_size(env_list);
    array = malloc(sizeof(char *) * (i + 1));
    if (!array)
        return (perror("Erro: alocação de envp_list_to_array"), NULL);
    i = 0;
    while(env_list) // "KEY=VALUE"
    {
        array[i] = my_strjoin(env_list->key, "=");
        array[i] = my_strjoin(array[i], env_list->value);
        env_list = env_list->next;
        i++;
    }
    array[i] = NULL;
    return (array);
}

char    **cmds_list_to_array(t_node *cmds)
{
    int     list_size;
    char    **args;

    list_size = env_list_size(cmds);
    array = malloc(sizeof(char *) * (list_size + 1));
    if (!args)
        return(perror("Erro: alocação de cmds_list_to_array"), NULL);
    while()
    {

    }
}

int     args_exec(char *path, t_node *list, char **env_array)
{
    if (!path)
        return (printf("Erro: Comando '%s' não encontrado\n", list->value[0]), ERROR);
    if (!list || !list->value)
        return (perror("Erro na lista de comandos"), ERROR);
    if (!env_array)
        return (perror("Erro ao converter lista de ambiente para array"), ERROR);
    return (NO_ERROR);
}
