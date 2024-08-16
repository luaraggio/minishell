/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:46:24 by lraggio           #+#    #+#             */
/*   Updated: 2024/08/15 18:56:13 by lraggio          ###   ########.fr       */
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
