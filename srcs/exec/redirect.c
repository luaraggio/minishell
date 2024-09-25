/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:39:17 by lraggio           #+#    #+#             */
/*   Updated: 2024/09/24 23:21:26 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*int do_redirections(t_node *node)
{
    int fd_redir_in;
    int fd_redir_out;
    int fd_redir_append;

    fd_redir_in = -1;
    fd_redir_out = -1;
    fd_redir_append = -1;
    if (node->token->type == REDIR_IN)
    {
        fd_redir_in = open(node->token->word, O_RDONLY);
        if (fd_redir_in < 0)
            return (perror("open redir_in"), ERROR);
        if (dup2(fd_redir_in, node->fd_in) == -1) // Redireciona o fd_redir_in_in do nó para o arquivo
            return (perror("dup2 fd_redir_in_in"), close(fd_redir_in), ERROR);
        close(fd_redir_in);
    }
    if (node->token->type == REDIR_OUT)
    {
        fd_redir_out = open(node->token->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_redir_out < 0)
            return (perror("open redir_out"), ERROR);
        if (dup2(fd_redir_out, node->fd_out) == -1)
            return (perror("dup2 fd_redir_out_out"), close(fd_redir_out), ERROR);
        close(fd_redir_out);
    }
    if (node->token->type == REDIR_APPEND)
    {
        fd_redir_append = open(node->token->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd_redir_append < 0)
            return (perror("open redir_append"), ERROR);
        if (dup2(fd_redir_append, node->fd_out) == -1)
            return (perror("dup2 fd_redir_append"), close(fd_redir_append), ERROR);
        close(fd_redir_append);
    }
    return (NO_ERROR);
}*/
