/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:07:06 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/17 15:06:57 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern volatile unsigned int	g_status;

char     *get_path_var(t_command *command)
{
    t_env   *get_path;
    char    *path;

    get_path = my_getenv_by_list("PATH", command->my_env);
    if (!get_path)
    {
        g_status = 127;
        my_putstr_fd("PATH variable is unset\n", 2);
        return (NULL);
    }
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
    {
        g_status = 127;
        my_putstr_fd("PATH variable is incorrectly set\n", STDERR_FILENO);
        return (NULL);
    }
    dir = my_split(path, ':');
    if (!dir)
        return (NULL);
    while (dir[i])
    {
        absolute_path = my_strjoin(dir[i], "/");
        absolute_path = my_strjoin(absolute_path, node->token->word);
        if (access(absolute_path, X_OK) == 0)
            return (free_matrix(dir), absolute_path);
        free(absolute_path);
        i++;
    }
    g_status = 127;
    return (free_matrix(dir), NULL);
}

char    **cmd_list_to_array(t_node *sentences)
{
    int         i; //iterador p/ atribuir a matriz
    int         cmd_list_size; //quantidade de tokens na linked list dos nós
    char        **args;
    t_tokens    *current_token;

    i = 0;
    cmd_list_size = count_tokens_in_node(sentences);
    args = malloc(sizeof(char *) * (cmd_list_size + 1));
    if (!args)
        return(perror("Erro: alocação de cmd_list_to_array"), NULL);
    while (sentences)
    {
        current_token = sentences->token;
        while (current_token)
        {
            args[i] = my_strdup(current_token->word);
            if (!args[i])
            {
                free_matrix(args);
                return(perror("Erro: alocação de token em args"), NULL);
            }
            i++;
            current_token = current_token->next;
        }
        sentences = sentences->next;
    }
    args[i] = NULL;
    return (args);
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

int     execve_args(char *path, t_node *list, char **env_array)
{
    if (!path)
        return (printf("bash: %s: command not found\n", list->token->word),
        g_status = 127, ERROR);
    if (!list || !list->token)
        return (perror("Erro na lista de comandos"), ERROR);
    if (!env_array)
        return (perror("Erro ao converter lista de ambiente para array"), ERROR);
    return (NO_ERROR);
}
