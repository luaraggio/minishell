/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:11:22 by lraggio           #+#    #+#             */
/*   Updated: 2024/08/15 21:06:12 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char     *get_path(t_command *command)
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

char    *get_absolute_path(t_command *command)
{
    
}


char    **envp_list_to_array(t_env *env_list)
{
    int         i; //quantidade de args
    char        **array;

    i = env_list_size(env_list);
    array = malloc(sizeof(char *) * (i + 1));
    if (!array)
    {
        perror("Erro: alocação de memória das nossas variáveis de ambiente");
        return (NULL);
    }
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

void    run_execve(t_command *command, t_node *list)
{
    t_node  *node;
    char    *path;
    char    **env_array;
    char    **args;

    node = list;
    args = node->value;
    env_array = envp_list_to_array(command->my_env);
    if (!env_array)
    {
        perror("Erro ao converter lista de ambiente para array");
        exit(EXIT_FAILURE);
    }
    path = get_path(command);
    if (!path)
    {
        free(env_array);
        exit(EXIT_FAILURE);
    }
    if (execve(path, args, env_array) == -1)
    {
        perror("Erro ao executar o comando");
        free(env_array); // Liberar memória alocada
        exit(EXIT_FAILURE);
    }
    free(env_array);
}
