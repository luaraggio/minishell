/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:08:26 by lraggio           #+#    #+#             */
/*   Updated: 2024/08/22 15:48:33 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int     has_pipe(t_node *list)
{
    char    **values;
    int     i;
    int     j;

    while (list)
    {
        values = list->value;
        j = 0;
        while (values[j])
        {
            i = 0;
            while(values[j][i])
            {
                if (is_pipe(values[j][i]) == TRUE)
                    return (TRUE);
                i++;
            }
            j++;
        }
        list = list->next;
    }
    return (FALSE);
}
