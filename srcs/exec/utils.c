/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:17:25 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/27 01:56:28 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	node_list_size(t_node *node)
{
	int	i;

	i = 0;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

void	close_node_fds(t_node *node)
{
	while (node)
	{
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		node = node->next;
	}
}

void	wait_cmds(t_node *node)
{
	while (node)
	{
		waitpid(node->pid, &node->exit_status, 0);
		node = node->next;
	}
}

void print_permission_denied(t_node *node)
{
	extern volatile unsigned int	g_status;

    if (node && node->token && node->token->word)
    {
        print_error("minishell: ");
        print_error(node->token->word);
        print_error(": Permission denied\n");
		g_status = 126;
    }
}
void print_cmd_not_found(t_node *node)
{
	extern volatile unsigned int	g_status;

    if (node && node->token && node->token->word)
    {
        print_error("minishell: ");
        print_error(node->token->word);
        print_error(": command not found\n");
		g_status = 127;
    }
}
