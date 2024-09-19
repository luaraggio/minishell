/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:45:47 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/19 18:04:50 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void    configure_fd(t_command *command, t_node *sentence)
{
    t_node  *current_node;

    current_node = sentence;
    while (current_node)
    {
        
    }
}*/

/*
void    configure_fds()
{

}
*/

void    close_fds(int fd_0, int fd_1)
{
    close(fd_0);
    close(fd_1);
}
