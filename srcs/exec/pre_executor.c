/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:55:49 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/24 23:22:09 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_pipe_or_not(t_node *sentence)
{
	if (sentence->next)
		return (TRUE);
	return (FALSE);
}

int has_redirect_or_not(t_node *sentence)
{
    
}

void print_fds(t_node *node, int i)
{
    printf("\033[36mNode %d:\033[0m\n", i);
    printf("fd_in = ");
    printf("%d\n", node->fd_in);
    printf("fd_out = ");
    printf("%d\n", node->fd_out);
}

int	make_pipe(t_node *sentence)
{
    t_node *node;
    int pipes;
    int i;

    i = 0;
    node = sentence;
    pipes = count_tokens_in_node(node) - 1;

	printf("\n");
	printf("\033[35mAntes do pipe\033[0m\n");
    while (node)
    {
        print_fds(node, i + 1);
        node = node->next;
        i++;
    }
	printf("\n");
    i = 0;
    node = sentence;
	printf("\033[35mDepois do pipe\033[0m\n");
    while (i < pipes && node && node->next)
    {
        pipe_config(node);
        print_fds(node, i + 1);
        node = node->next;
        i++;
    }
    if (node)
        print_fds(node, i + 1);
	printf("\n");
    return NO_ERROR;
}


int	pipe_config(t_node *node)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror((strerror(errno))), ERROR);
	node->fd_out = pipe_fd[1];
	node->next->fd_in = pipe_fd[0];
	return (NO_ERROR);
}
