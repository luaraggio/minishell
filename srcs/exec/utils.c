/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:17:25 by lraggio           #+#    #+#             */
/*   Updated: 2024/10/09 16:05:21 by lraggio          ###   ########.fr       */
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

void	do_dup2(t_node *node)
{
	if (node->fd_out != STDOUT_FILENO)
        dup2(node->fd_out, STDOUT_FILENO);
    if (node->fd_in != STDIN_FILENO)
        dup2(node->fd_in, STDIN_FILENO);
}

void	close_node_fds(t_node *node)
{
	while (node->next != NULL)
	{
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		node = node->next;
	}
}

void	close_all_node_fds(t_node *node)
{
	while (node)
	{
		//printf("closing:%s\n", node->token->word);
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		node = node->next;
	}
}

void	wait_cmds(t_node *node)
{
	t_node	*current_node;

	current_node = node;
	while (current_node)
	{
		if (current_node->pid != 0)
			waitpid(current_node->pid, &current_node->exit_status, 0);
		current_node = current_node->next;
	}
}

void	update_status(t_node *sentence)
{
	t_node	*node;

	node = sentence;
	while (node)
	{
		if (node->exit_status != 0)
		{
				if (node->exit_status >= 255)
					g_status(WEXITSTATUS(node->exit_status));
				else
					g_status(node->exit_status);
		}
		else
			g_status(NO_ERROR);
		node = node->next;
	}
}
