/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:46:24 by lraggio           #+#    #+#             */
/*   Updated: 2024/08/20 13:29:24 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int     env_list_size(t_env *list)
{
    int         i;

    i = 0;
    while (list)
    {
        i++;
        list = list->next;
    }
    return (i);
}

void	print_env_array(char **envp)
{
    int     i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
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

void    free_matrix(char **matrix)
{
    int     i;

    if (!matrix)
        return ;

    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}
